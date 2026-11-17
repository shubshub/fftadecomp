# 0x081223C8 - queue wrapper: a 28-byte stack command through the scheduler entry func_08121B8C: bytes identical, refused (a stack descriptor passed to the scheduler entry func_08121B8C, then a following call) (60 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u8 func_081223C8(source, offset, second)` builds a 28-byte command on the stack (the object word from
`source + 0xC`, `offset + source->base` and `second` as halfwords at +0x14 and +0x16), queues it with the scheduler entry
`func_08121B8C(func_08121FB8, 0x10, &command, 0)` and returns `func_08122404(task)` narrowed to `u8`. It is called by
`func_08122B14` (0x08122B3C) and `func_08122B50` (0x08122B78). The whole function:

```
081223C8  push {lr}
081223CA  sub  sp, #0x1c
081223D2  ldr  r3, [r0, #0xc]
081223D4  str  r3, [sp, #4]       @ command.object
081223DE  strh r1, [r3, #0x14]    @ command.first (r3 = sp)
081223E2  strh r2, [r0, #0x16]    @ command.second (r0 = sp)
081223E4  ldr  r0, =func_08121FB8
081223E6  movs r1, #0x10
081223E8  mov  r2, sp             @ &command
081223EA  movs r3, #0
081223EC  bl   0x08121B8C
081223F0  bl   0x08122404         @ the new task, R2 still holding &command
081223F4  lsls r0, r0, #0x18
081223F6  lsrs r0, r0, #0x18
```

## The index

`symbols/functions.txt` has `081223C8 08122404 60 30 return` and `config/functions.json` the same extent with 30 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 25 reachable instructions, so the instruction column is the halfword count (30). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`.

## Byte identity

`081223C8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081223C8, with every callee bound to its ROM address and every data word to the address its symbol names (2 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 60-byte symbol equals the ROM span `[0x081223C8, 0x08122404)`: SHA-256 `6c00d5e0a96c66737b9b478f69f6d452063a2820b7a87a788e5930fb279d78fa` for both. `.text` is exactly 60 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: the function has no data relocation.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081223C8.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee 0x08121B8C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1` and 7 other scheduler selectors (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` and `conditional-scheduler-three-per-path-live-alias-v1` (2) | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-rom-table-copy-v1` and 15 other selectors (18) | `buffer callee 0x08121B8C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08121B8C: buffer callee 0x08005954: buffer callee 0x08142250: structural inventory is not closed` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 165 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback word `func_08121FB8` puts the default run on the function-literal path; with no named data it
falls back to the function-buffer proof, which walks `&command` through `func_08121B8C` into `func_08005954` and refuses
there: `stack aliases cannot cross calls in caller-clobbered registers; function-buffer proof: buffer callee
0x08121B8C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies`.
The buffer selectors stop at the scheduler's callback thunk (`... buffer callee 0x08142250: non-leaf indirect control
flow requires linked CFG verification`). Of the scheduler selectors, `conditional-scheduler-entry-descriptor-calls-v1`,
which pins `func_08121B8C`, requires the entry call to be the function's only call (`len(calls) == 1` in
`tools/scheduler_entry_profile.py:65`) and refuses `scheduler entry contract requires one actual pinned entry call`:
the task it returns is passed to `func_08122404`; ten others give `scheduler branches exceed
the explicit call-site or target bounds`.

The scheduler call-site issue reports `MATCH - byte identical` for this function under its per-site rule alone.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (admitted by the per-site rule alone in the prototype)
