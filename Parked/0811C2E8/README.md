# 0x0811C2E8 - camera pan callback: two coordinate conversions through func_080DC224: bytes identical, refused (the jump table of 0x080C7EA4, reached through func_080DC224 and func_080DD6E0) (548 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `int func_0811C2E8(owner, command, state)` is a phase callback (switch on `command->phase`: 0, 1, 0x100 to 0x103)
registered by three function words at 0x08395388, 0x08395390 and 0x083953A8 in the ROM callback table. Phase 0 keeps
`command->kind - 0x78` as an index and the object; 0x100 starts a BG load (`func_080DC1E8(object, 0, 0, 6, 0x0600F9E0,
0x06005000, owner)`); 0x101 waits for it, sets the BG registers (`func_080034B8`, `func_08003A74`, `func_08003A80`,
`func_080035A8`), converts the table point `data_083A6C18[index]` with `func_0801C960(x, y, &x, &y)` and then with
`func_080DC224(object, x, y, &x, &y)` (local outputs, the second in the outgoing word), writes the BG offsets
(`func_08003508`, `func_08003558`), converts the object's own position (`func_080DBDC8(object, &state->x, &state->y)`,
then `func_080DC224` into `&target_x`, `&target_y`), starts two 90-frame interpolations (`func_080E0608`), an effect
(`func_080D3E9C(data_0894DD84, owner)`) and a sprite (`func_080DFD8C(data_083A6C10, ...)`); 0x102 and 0x103 step the
interpolations and clean up.

`func_080DC224` calls `func_080DD6E0`, which calls `func_080C7EA4`, a function with a guarded jump table; the effect
started by `func_080D3E9C` reaches the scheduler `func_08005B6C`.

## The index

`symbols/functions.txt` has `0811C2E8 0811C50C 548 274 return` and `config/functions.json` the same extent with 274 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 228 reachable instructions, so the instruction column is the halfword count (274). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0811C2E8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811C2E8, with every callee bound to its ROM address and every data word to the address its symbol names (26 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 548-byte symbol equals the ROM span `[0x0811C2E8, 0x0811C50C)`: SHA-256 `2713c6afd540b11a6b09687e991e9c57b58e249e8a1e721614d684ab5b44cdb5` for both. `.text` is exactly 548 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A6C10": "0x083A6C10"`):

`data_083A6C10`, `data_083A6C18`, `data_0894DD84`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811C2E8.c` and the data symbols above added: the default run and all 213 selector values. None matched.

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
| `bounded-buffer-guarded-callee-aliases-v1` and `bounded-buffer-guarded-bios-division-v1` (2) | `buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 164 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), bounded-buffer (7), function-address (6), arithmetic-runtime (5), control-flow (1), -O0 (1).

## Cause

The default run (named data, direct calls) walks `&x` and `&y` into `func_080DC224`, through `func_080DD6E0`, to
the dispatch of `func_080C7EA4` and refuses there: `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee
0x080C7EA4: unresolved program-counter write`. Two selectors of unmodified kit 18dcc516, `bounded-buffer-guarded-callee-aliases-v1`
and `bounded-buffer-guarded-bios-division-v1`, get past it and stop where the switch-callee issue reports its prototype
stopping: at the scheduler reached inside the walked callee `func_080D3E9C` (`buffer callee 0x080D3E9C: buffer callee
0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG
verification`), which the scheduler call-site issue leaves out (its rule applies to the owner's own calls).
`bounded-buffer-guarded-switch-v1` stops inside `func_080DC224` (`consumer observes discarded return scratch before a
killing write`), and the stack-index selectors refuse the pointer-bearing outgoing word.

## Source notes

From the attempt, not reviewed: the two VRAM addresses are written as casts of integer constants
(`(void *)0x0600F9E0`, `(void *)0x06005000`), as the ROM pool holds them as numbers.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (listed under "Not covered": the scheduler reached inside the walked callee 080D3E9C)
