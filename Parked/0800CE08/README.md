# 0x0800CE08 - scanline effect set-up with line tables: bytes identical, refused (local copies of ROM tables through func_081443FC, then indexed) (254 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0800CE08(mode, value, destination)` is the one-bank
sibling of 0x0800CC8C. It copies the 12-byte callback table `data_0814980C` (`ldm`/`stm` at 0x0800CE2C-0x0800CE2E) and
the `u16[3]` tables `data_08149818` and `data_08149806` (through `func_081443FC` at 0x0800CE38 and 0x0800CE44) to the
stack, creates the object with `func_0800C3CC(callbacks[mode], payload_bytes[mode], element_sizes[mode],
destination)`, takes one, two or four 160-entry line tables from `func_0800C614(object)` and sets every line to
`value`. Callers: the matched `src/080D9170.c`, `src/080D9350.c` and `src/080D9488.c`, and 0x080D8E00 and 0x080D9528.

The index row `0800CE08 0800CF06 254 127 return` has the right extent; 127 is half the byte count, and the reachable
count is 114 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`0800CE08.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800CE08, with every callee and data symbol bound to its
ROM address (6 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 254-byte symbol equals the ROM span `[0x0800CE08, 0x0800CF06)`:
SHA-256 `d95443032f3cea8de14c575311dc2e598097ace702a3e60b825b4d6cc9da8273` for both. `.text` is 256 bytes: the symbol
and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below).
`plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0800CE08.c` and `data_08149806`,
`data_0814980C`, `data_08149818` added to `config/data_symbols.json` (each at the address its name gives): the default
run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `stack index: index range is not 4-byte aligned on every path; index has no defined source (no premise can be stated)` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. Under the stack-index selectors the proof cannot bound the register index into the copied
tables (`stack index: index range is not 4-byte aligned on every path; index has no defined source (no premise can be
stated)`).

kit issue: shubshub/fftadecomp-kit#240
