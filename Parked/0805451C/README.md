# 0x0805451C - count of eligible units in the sorted list: bytes identical, refused (a local list filled by a jump-table callee) (128 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0805451C()` gets the unit order for the current
selection mode from `func_08071DC8(selected, indices)` into a local `u8 indices[24]` (0x08054526, `mov r1, sp`), skips
0xFF entries and units whose id is 0, 2 or 15 or that are not active, copies the rest to `data_0200F428->indices` and
returns their count. Callers: the matched `src/08055C38.c` and 0x08054E14.

The index row `0805451C 0805459C 128 54 return` is right (54 reachable instructions).

## Byte identity

`0805451C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0805451C, with every callee and data symbol bound to its
ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 128-byte symbol equals the ROM span `[0x0805451C, 0x0805459C)`:
SHA-256 `d86d2a25445a362ca8594bc4110a4e70e3b0babb89efc3d5c646b1fb6c0bc6e3` for both. `.text` is exactly 128 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0805451C.c` (no data symbol to add): the
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

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
