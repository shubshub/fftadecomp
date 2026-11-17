# 0x0800CC8C - scanline effect set-up with line records: bytes identical, refused (local copies of ROM tables through func_081443FC, then indexed) (380 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0800CC8C(mode, a, b, c, value, d, destination)` copies
a 24-byte callback table (`data_081497E8`, two banks of three; `ldm`/`stm` at 0x0800CCCA-0x0800CCD0) and two `u16[3]`
tables (`data_08149800`, `data_08149806`; through `func_081443FC` at 0x0800CCDA and 0x0800CCE6) to the stack. It takes
bank `mode >> 7` and kind `mode & 0x7F`, creates the effect object with `func_0800C3CC(callback, payload_bytes[kind],
element_sizes[kind], destination)`, collects one, two or four line records from `func_0800C614(object)` in a local
pointer array, writes `value` and the four packed bytes into each record with lines 0 to 159, enables the object with
`func_0800C628(object, 1)` and returns it. No `bl` or function word in the ROM refers to 0x0800CC8C; its one-bank
sibling 0x0800CE08 has five callers.

The index row `0800CC8C 0800CE08 380 166 return` is right (166 reachable instructions).

## Byte identity

`0800CC8C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800CC8C, with every callee and data symbol bound to its
ROM address (7 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 380-byte symbol equals the ROM span `[0x0800CC8C, 0x0800CE08)`:
SHA-256 `3a4f66e26915a587a2addb9f65e53c4c4fe473060cad33ff4337bd18b2c64e05` for both. `.text` is exactly 380 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0800CC8C.c` and `data_081497E8`,
`data_08149800`, `data_08149806` added to `config/data_symbols.json` (each at the address its name gives): the default
run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `inconsistent possible pointer offsets at control-flow join` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. The two copies here are followed by register indices into the copies (`payload_bytes[kind]`,
`element_sizes[kind]`, and the callback by bank and kind); under the stack-index selectors the proof stops at a join
(`inconsistent possible pointer offsets at control-flow join`).

## Source notes

- `set_line` is a `static inline` helper used once, as the loop body; it fills one line record from the packed entry.
  It needs a ruling under the helper rule.
- The three ROM tables are not in `config/data_symbols.json`; the refusal runs add them (above).

kit issue: shubshub/fftadecomp-kit#240
