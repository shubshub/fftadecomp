# 0x0800D090 - affine window task creation (kind 2): bytes identical, refused (a variable index into a stack copy of a ROM table) (216 bytes)

Attempt 2026-11-18, kit 750d2fb7, decomp main 52ef3ba2f9.
`func_0800D090(target, x, y, unknown_34, unknown_36, width, height)` is 0x0800CF08 with kind 2: it copies
`data_08149820` to the stack, creates the task with `func_0800C3CC(func_0800D3BC, 0x2B8, 0x10, targets[target - 2])`
(0x0800D0EE), fills the same rectangle, origin and start fields, stores the two extra halfwords and calls
`func_0800CAF0(window, 1)` (0x0800D148). No `bl` or literal word in the ROM reaches it.

The index row `0800D090 0800D168 216 108 return` has the right extent; 108 is half the byte count, and the reachable
count is 100 (the kit's own CFG refinement). `config/functions.json` has the same extent and count.

## Byte identity

`0800D090.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0800D090, with every callee and data symbol bound to its
ROM address (3 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 216-byte symbol equals the ROM span `[0x0800D090, 0x0800D168)`:
SHA-256 `81128855f07b0c756a1aae32da0afce48e9c6be50df038267d0131930478901e` for both. `.text` is exactly 216 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 750d2fb7, `match.py --root . --no-write` with this source copied to `src/0800D090.c` and `data_08149820` added to
`config/data_symbols.json` (each at the address its name gives): the default run, the two stack-index selectors and
the ROM-table-copy selector the #200 comment discusses, and the selectors earlier notes name. None matched.

| Selector | Result |
|---|---|
| default and `named-data-buffer-rom-table-copy-v1` (2) | `unsupported stack-address materialization` |
| `named-data-buffer-stack-index-v1` | `stack index: the premise rows of 0x0800D090 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)`; the row it prints: site `0x0800D0E8`, expression `(((entry_R0 << 24) >> 22) - 8)`, bound 5 |
| `named-data-buffer-stack-index-v2` | `stack index: the premise rows of 0x0800D090 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)`; the row it prints: site `0x0800D0E8`, expression `(u32)(((entry_R0 << 24) >> 22) - 8)`, bound 5 |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2`, each with the row it prints added to `config/stack_index_premises.json` as a throwaway entry (not reviewed) | `ROM table copy owner requires named data or an object initialiser and excludes function literals and switches` |

## Cause

As for 0x0800CF08: `unsupported stack-address materialization` by default; under both stack-index selectors a premise
row for the index at 0x0800D0E8 (bound 5), then, with a throwaway entry, the function-literal refusal the #200 comment
quotes.

## Source notes

- Needs `data_08149820` in `config/data_symbols.json`.

kit issue: shubshub/fftadecomp-kit#200 (comment); related: shubshub/fftadecomp-kit#135
