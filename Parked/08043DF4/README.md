# 0x08043DF4 - five-entry item menu set-up: bytes identical, refused (a local copy of a ROM id table through func_081443FC) (216 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08043DF4(state, kind)` copies the five item ids
`data_081499AC` (`u16[5]`) to the stack with `func_081443FC` (0x08043E08) and builds up to five menu items in
`state->storage`, item 1 only when `func_080C9540(0x303)` holds and item 2 only when `func_080C9540(0x559)` holds;
each item takes its value from `g_table_085567F0[id]` and its size from `data_0852A13E[id]`. It then fills the menu
header (table `g_table_08526680`, height `count * 2 + 3`, at most 15) and returns the count. Its caller is 0x08043468.
The matched `src/08043ECC.c` has the same copy and loop without the two predicate calls.

The index row `08043DF4 08043ECC 216 108 return` has the right extent; 108 is half the byte count, and the reachable
count is 91 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`08043DF4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08043DF4, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 216-byte symbol equals the ROM span `[0x08043DF4, 0x08043ECC)`:
SHA-256 `af6b98439de8cc3d1095111c82716cf21fc9c9d7d1d33cc67286bf5854143da3` for both. `.text` is exactly 216 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08043DF4.c` and `data_081499AC` added to
`config/data_symbols.json` (each at the address its name gives): the default run and the selectors the kit issue and
the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `finite small copy requires only its exact helper call` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. `named-data-buffer-finite-small-copy-binding-v1` binds the copy but refuses the two
`func_080C9540` calls in the loop: `finite small copy requires only its exact helper call`.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
