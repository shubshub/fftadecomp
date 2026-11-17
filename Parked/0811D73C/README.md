# 0x0811D73C - rising particle callback: coordinate conversions through func_080DC224: bytes identical, refused (the jump table of 0x080C7EA4, reached through func_080DC224 and func_080DD6E0) (360 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811D73C(context, command, state)` is a phase callback (switch on `command->state`: 0, 1, 0x100 to
0x103) of the task `func_0811DA64`, whose pool holds its function word (0x0811DB78). Phase 0 records the object and a
source pointer and reads the object's position into the state (`func_080DBDC8`); 0x100 sets a 25-frame timer; 0x101
waits for it and for `func_080DFAD0(*source)`, converts the position with `func_080DC224(object, x, y, &a, &b)` (local
outputs, `&b` in the outgoing word), writes the BG offsets (`func_08003508`, `func_08003558`), hides the object
(`func_080DBEB4`), and starts a particle (`func_080D6098(x, y, 0, 1, 7, state->particle_data, data_083A6F2C,
context)`), an effect (`func_08147EC8(0x70, 0x10, 0x96, 8)`, polled later with `func_081484CC`), an interpolation and a record
(`func_080DFD8C(data_083A70B4, ...)`); 0x102 steps the interpolation, converts again with `func_080DC224`, and waits for
the effect (`func_081484CC`) and the particle (`func_080D6134`).

## The index

`symbols/functions.txt` has `0811D73C 0811D8A4 360 180 return` and `config/functions.json` the same extent with 180 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 160 reachable instructions, so the instruction column is the halfword count (180). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0811D73C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811D73C, with every callee bound to its ROM address and every data word to the address its symbol names (16 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 360-byte symbol equals the ROM span `[0x0811D73C, 0x0811D8A4)`: SHA-256 `0d21500f051bd0f1b0fc26223d028fbbc1b0ee7ea3e38bb616991b9f8fcea7fa` for both. `.text` is exactly 360 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A6F2C": "0x083A6F2C"`):

`data_083A6F2C`, `data_083A70B4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811D73C.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 7 other scheduler selectors (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` and `conditional-scheduler-three-per-path-live-alias-v1` (2) | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 11 other selectors (14) | `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x080DC224: consumer observes discarded return scratch before a killing write` |
| `bounded-buffer-guarded-callee-aliases-v1` and `bounded-buffer-guarded-bios-division-v1` (2) | `buffer callee 0x080D6134: buffer callee 0x08005B58: buffer callee 0x080058A4: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 164 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), bounded-buffer (7), function-address (6), arithmetic-runtime (5), control-flow (1), -O0 (1).

## Cause

The default run (named data, direct calls) walks `&a` and `&b` into `func_080DC224`, through `func_080DD6E0`, to
the dispatch of `func_080C7EA4` and refuses there: `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee
0x080C7EA4: unresolved program-counter write`. That is the switch-callee issue's guarded layout (one unsigned-guarded
complete table). Two selectors of unmodified kit 18dcc516 already get past it, `bounded-buffer-guarded-callee-aliases-v1`
and `bounded-buffer-guarded-bios-division-v1`, and stop where the issue reports its prototype stopping: at the dynamic
task callback reached through the particle routine, `buffer callee 0x080D6134: buffer callee 0x08005B58: buffer callee
0x080058A4: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`.
`bounded-buffer-guarded-switch-v1` stops inside `func_080DC224` (`consumer observes discarded return scratch before a
killing write`), and the stack-index selectors refuse the pointer-bearing outgoing word. The scheduler call-site issue
lists `08005B58` -> `080058A4` among the entries it does not cover.

## Source notes

From the attempt, not reviewed: `case 1: break;` is written after `case 0x102`, where the attempt placed
it; it is recorded as a doubt.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (listed under "Not covered": the dynamic callback of 08005B58 -> 080058A4)
