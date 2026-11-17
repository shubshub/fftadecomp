# 0x08067FFC - units outside seven states: bytes identical, refused (a local list filled by a jump-table callee) (128 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08067FFC(output)` gets the unit order from
`func_08071DC8(g_state_020020D0.selected, indices)` (0x08068008, `mov r1, sp`), and for every listed unit
(`&g_state_02000080[index]`, 0x108-byte records) whose state `func_080C7EA4(unit, 1)` is not 2, 8, 0x5E, 10, 4, 9 or
12, stores the unit pointer to `output` when that is not null and counts it. The matched `src/0806617C.c` calls it.

The index row `08067FFC 0806807C 128 64 return` has the right extent; 64 is half the byte count, and the reachable
count is 57 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`08067FFC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08067FFC, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 128-byte symbol equals the ROM span `[0x08067FFC, 0x0806807C)`:
SHA-256 `7343f254140b943aa289b92b69a11cbb16be211aed04c79e2168f5ed9f285d65` for both. `.text` is exactly 128 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08067FFC.c` (no data symbol to add): the
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

## Source notes

- `unit != 0 &&` tests the address of an array element, which is never null; the ROM keeps the test (`cmp r4, #0; beq`
  at 0x08068038), so it is inert code the ROM shows and needs an address comment before it ships.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
