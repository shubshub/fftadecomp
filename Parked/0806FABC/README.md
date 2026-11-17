# 0x0806FABC - item name and granted ability names: bytes identical, refused (a local list filled by a jump-table callee) (148 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0806FABC(menu, id)` draws the item's name
(`g_table_08526680[g_table_0851D180[id].name]`) with `func_0806FFAC`, and unless the item's kind is 0x1B gets up to
three granted abilities from `func_080C8D14(id, &list)` into a local (0x0806FAF6, `mov r1, sp`) and draws each name
(`g_table_085567F0[...]`) on the following rows. Callers: the matched `src/0806F7B8.c` and `src/0806F8DC.c`.

The index row `0806FABC 0806FB50 148 74 return` has the right extent; 74 is half the byte count, and the reachable
count is 64 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0806FABC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0806FABC, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 148-byte symbol equals the ROM span `[0x0806FABC, 0x0806FB50)`:
SHA-256 `7bd5e7ff8973ab728606c442f41f828a12ea38f7d76774cdd247fe84d546848b` for both. `.text` is exactly 148 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0806FABC.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x080C8D14: unresolved program-counter write` |

## Cause

`func_080C8D14` (matched) clears the 0x1C-byte list through `_call_via_r2` and dispatches through a jump table that is
loaded before its guard, with a default case that loops to itself. The walk refuses at its `mov pc`, and neither
switch selector knows that layout, so both refuse at the same place.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
