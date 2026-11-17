# 0x08022DD0 - two callbacks in table order: bytes identical, refused (a local copy of a ROM order table through func_081443FC) (84 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08022DD0()` copies the two-byte order table
`data_08149994` to the stack with `func_081443FC` (0x08022DDA, destination `mov r0, sp`, count 2). For each index in
that order whose callback in `data_03002710.callbacks` is set, it sets the index's flag byte to 0xFF and calls
`callbacks[index](index, &flags[index])` through `_call_via_r2` (`bl 0x0814224C` at 0x08022E08). Callers: the matched
`src/08024108.c`, `src/081235E4.c` and `src/08125560.c`.

The index row `08022DD0 08022E24 84 42 return` has the right extent; 42 is half the byte count, and the reachable
count is 35 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`08022DD0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08022DD0, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 84-byte symbol equals the ROM span `[0x08022DD0, 0x08022E24)`:
SHA-256 `1145e6bbcdbedfe03cd2dc183f61eb7802b30952c8cbb10be49f84d521a63d6d` for both. `.text` is exactly 84 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08022DD0.c` and `data_08149994` added to
`config/data_symbols.json` (each at the address its name gives): the default run and the selectors the kit issue and
the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `named-data-buffer-rom-table-copy-v1` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `conditional-known-query-stack-buffer-v1` | `refused: function-address evidence does not support runtime call thunks` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. The stack-index and ROM-table-copy selectors refuse this function earlier, on the
`_call_via_r2` call (`acyclic owner excludes arithmetic runtimes and indirect thunks`).

## Source notes

- An earlier kit crashed with a traceback on `conditional-known-query-stack-buffer-v1`; at 18dcc516 it refuses
  normally (above).

kit issue: shubshub/fftadecomp-kit#240
