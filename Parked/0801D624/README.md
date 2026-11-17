# 0x0801D624 - map cell edge flags: bytes identical, refused (variable index into a local u8[4] with pointer-bearing outgoing words) (500 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0801D624(column, row, mode)` gets the cell's height (`func_0801CC18`), its world and screen position
(`func_0801CA78`, `func_0801C918`, both with local outputs), and for the four neighbours (offsets from the stack copy
of `data_08149904`) sets `flags[i]` when `func_0801EC28` returns the value of `func_0801E63C`. Then, for each clear
flag, it tests the map cell at the offset from `data_081498F4` (`func_0801AD38(0)`), and passes the flags to
`func_0801D130(column, row, x, y, flags, mode)` (0x0801D7FE). Callers: three sites in 0x08092784 (0x0809354C,
0x08093628, 0x08093638; it has a `Parked/` entry), 0x08098A88 (0x08098B64) and 0x080B5A08 (0x080B69A6).

The index row `0801D624 0801D818 500 250 return` has the right extent; 250 is half the byte count, and the reachable
count is 235 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0801D624.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801D624, with every callee and data symbol bound to its
ROM address (9 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 500-byte symbol equals the ROM span `[0x0801D624, 0x0801D818)`:
SHA-256 `0995400544f94c7a18ff53fa3d5e4ad40d16cf71d6b202d550c0d0537acbcceb` for both. `.text` is exactly 500 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0801D624.c` and `data_08149904` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the two stack-index selectors and
the ROM-table-copy selector the #200 comment discusses, and the selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default and `named-data-buffer-rom-table-copy-v1` (2) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |

## Cause

The default path refuses the variable index into the local flags (`unsupported stack-alias use or escape`). Both
stack-index selectors refuse it because the frame also holds pointer-bearing words (the outgoing `&screenY`/`&depth`
arguments): `variable stack indices exclude pointer-bearing or return-carrying local words`, the #200 comment's row.

## Source notes

- Needs `data_08149904` in `config/data_symbols.json` (`data_081498F4` is already there).

kit issue: shubshub/fftadecomp-kit#200 (comment)
