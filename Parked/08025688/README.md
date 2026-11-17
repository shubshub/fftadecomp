# 0x08025688 - menu close with a delayed task: bytes identical, refused (a local descriptor passed to the scheduler entry after a three-way choice) (152 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08025688(cursor, value, arg)` closes the menu in
`data_0200F438` (enabled 0, mode 12, status 0), sets bits 10 and 11 of the display control in
`g_control_flags_03000940`, stores the cursor (`value` when `cursor` is 0, `cursor | 0x8000` when bit 14 is clear,
`cursor` otherwise), records `value` and `arg` in `g_state_020020D0`, and starts `func_08029188` through the scheduler
entry, `func_08005954(data_0200F438->manager, func_08029188, 0xA4, &descriptor, 0)` (0x08025708), with a 28-byte local
descriptor whose delay at +0x14 is 11; the descriptor is in R3 and the parent in the outgoing word. It is a sibling of
the matched `src/08025720.c`. Callers: the matched `src/08029528.c` and `src/080A75BC.c`, and five unmatched
functions.

The index row `08025688 08025720 152 76 return` has the right extent; 76 is half the byte count, and the reachable
count is 67 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`08025688.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08025688, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 152-byte symbol equals the ROM span `[0x08025688, 0x08025720)`:
SHA-256 `88ce3c072865b14b4406c3e68726c284994395c48bdf5ebbbbdd89619983b19c` for both. `.text` is exactly 152 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08025688.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-twenty-four-target-following-calls-v1`, `conditional-scheduler-three-per-path-calls-v1`, `conditional-scheduler-sequential-leaf-output-calls-v1`, `conditional-scheduler-sequential-killed-alias-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `direct scheduler manager requires one straight-line named data load` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `manager field requires exactly two zero-offset word dereferences` |
| `conditional-scheduler-manager-offset-v1` | `manager offset requires a finite straight-line load chain` |
| `conditional-scheduler-manager-paths-v1` | `manager paths require immediate word loads at every first definition` |

## Cause

On the function-literal path (the callback word `func_08029188`, with named data) there is no buffer proof, so the
descriptor address in R3 refuses at the scheduler call. The 25 scheduler selectors apply the descriptor contract but
bound the whole caller's shape; here the three-way cursor store before the call copies the state pointer and reloads
it after the join, and they refuse on branch, call-site and load-chain counts. The sibling's selector,
`conditional-scheduler-manager-offset-v1`, wants a straight-line load chain for the manager.

kit issue: shubshub/fftadecomp-kit#237
