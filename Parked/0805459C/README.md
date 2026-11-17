# 0x0805459C - count of available units in the sorted list: bytes identical, refused (a local list filled by a jump-table callee) (160 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0805459C()` gets the unit order for the current
selection mode from `func_08071DC8(selected, indices)` into a local `u8 indices[24]` (0x080545A6, `mov r1, sp`), skips
0xFF entries and units that fail its five status tests (present, three flag bits and a pair of status bytes), copies
the rest to `data_0200F428->entries` and returns their count. Callers: 0x08055F10 and 0x080570D8. It is 0x0805451C's
sibling, with the same two pool words for the selection (0x020020D0 and 0xFFFFDF30).

The index row `0805459C 0805463C 160 70 return` is right (70 reachable instructions).

## Byte identity

`0805459C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0805459C, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 160-byte symbol equals the ROM span `[0x0805459C, 0x0805463C)`:
SHA-256 `a4b7692442bf9762f6a4cfd42103319e40df46dbc95d3395d836f23ed436621a` for both. `.text` is exactly 160 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0805459C.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x08071DC8: unresolved program-counter write` |
| `bounded-buffer-guarded-switch-v1` | `buffer callee 0x08071DC8: unsupported stack-alias use or escape` |
| `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x08071DC8: jump-table buffer callee excludes calls and local BL control` |

## Cause

`func_08071DC8` (872 bytes, parked) dispatches on the mode through a guarded six-entry jump table and writes the list
with a variable index (`adds r1, r7, r0` at 0x08072052). The default walk follows the local list into it and refuses
at the dispatch (`unresolved program-counter write`). `bounded-buffer-guarded-switch-v1` decodes the table and refuses
the variable-index store (`unsupported stack-alias use or escape`), and the selective nested-output selector, the only
one that follows a jump table inside a callee, excludes the callee's calls.

kit issue: shubshub/fftadecomp-kit#241
