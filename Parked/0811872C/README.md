# 0x0811872C - group entrance callback: three scheduler sites, one of them in a loop: bytes identical, refused (local aliases across calls on the function-literal path; the scheduler selectors bound the number of sites and refuse the loop) (576 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811872C(task, event, s)` is a phase callback (switch on `event->phase`: 0, 1, 0x100 to 0x105)
registered by its function word at 0x083951E8 in the ROM callback table. Phase 0 starts a loader
(`func_080E03F8(actor, data_083A6068, flags, 1, 0, task)`) and writes one palette colour (`data_03003860[0x71] =
0x39CE`); 0x100 counts the group (`func_080DD494`) and, in the alternate mode, calls `func_080D8924(actor, 0, 0x14,
task)` and skips ahead; 0x101 starts one child per member in a `u8` loop, each with the same 28-byte stack descriptor
(`request.ready = &s->ready[i]; request.slot = i;`), `func_08005B6C(func_0811836C, 0x1C, &request, task)` at 0x0811882C;
0x102 starts two more children sharing a second stack descriptor, `func_08005B6C(func_08118500, 0x14, &banner, task)`
(0x08118872) and `func_08005B6C(func_08118590, 0x3C, &banner, task)` (0x08118880); 0x103 to 0x105 wait for the
children and run one `func_080DCFE4` effect per member.

## The index

`symbols/functions.txt` has `0811872C 0811896C 576 288 return` and `config/functions.json` the same extent with 288 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 249 reachable instructions, so the instruction column is the halfword count (288). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`0811872C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811872C, with every callee bound to its ROM address and every data word to the address its symbol names (16 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 576-byte symbol equals the ROM span `[0x0811872C, 0x0811896C)`: SHA-256 `72b7becdb8621e7266bb5daf4dc8ec9d4e6e67cbab99c61eaa54677d7ec633c8` for both. `.text` is exactly 576 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A6068": "0x083A6068"`):

`data_083A6068`, `data_083A60A4`, `data_083A60B8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811872C.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 4 other scheduler selectors (7) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1` and `conditional-scheduler-sequential-killed-alias-calls-v1` (3) | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler successor must add exactly one` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` and `conditional-scheduler-three-per-path-live-alias-v1` (2) | `live-alias callee copies SP while a saved alias is on the stack` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-rom-table-copy-v1` and 15 other selectors (18) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: structural inventory is not closed` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 165 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback words (`func_0811836C`, `func_08118500`, `func_08118590`) and the named data put the default run
on the function-literal path, which has no buffer proof: `stack aliases cannot cross calls in caller-clobbered
registers`. The buffer selectors walk the descriptor into the scheduler and stop at its callback thunk
(`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires
linked CFG verification`). The 25 scheduler selectors refuse the caller's shape, not the sites: 7 give
`scheduler branches exceed the explicit call-site or target bounds`, 4 `scheduler contract requires one actual scheduler
call`, 3 `predicate composition excludes CFG cycles`, the counts the scheduler call-site issue's table gives. The one looped site
(0x0811882C) has only the descriptor in R2.

## Source notes

From the attempt, not reviewed: the alternate branch of phase 0x100 stores `s->timer = 1` before and
after the `func_080D8924` call; the ROM stores it twice (`strb r4, [r5, #7]` at 0x081187E0 and 0x081187EE), so the
second store is ROM-shown code, not a respelling.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (admitted by the per-site rule alone in the prototype)
