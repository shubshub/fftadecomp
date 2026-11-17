# 0x0801E458 - background layer set-up: bytes identical, refused (local copies of ROM tables through func_081443FC) (244 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0801E458(layer, size, priority, x, y, tiles, palette)`
copies two `u16[4]` attribute tables (`g_object_08149914`, `g_object_0814991C`; through `func_081443FC` at 0x0801E48E
and 0x0801E49C) and the four-pointer table `g_object_08149924` (`ldm`/`stm` at 0x0801E4AA-0x0801E4AC) to the stack. It
builds the layer's control word from `func_08003A74(palette)`, `func_08003A80(tiles)` and the two table entries and
sets it with `func_080034B8`, sets the offsets with `func_08003508` and `func_08003558`, and stores the width and
height (`data_0836DA94[size] >> 3`, `data_0836DA9C[size] >> 3`), tiles and palette into the record `layers[layer]`
points to. Callers: the matched `src/0801D494.c`, `src/08022874.c`, `src/0802D0B0.c`, `src/0812A084.c` and
`src/0812B340.c`, and seven unmatched functions.

The index row `0801E458 0801E54C 244 122 return` has the right extent; 122 is half the byte count, and the reachable
count is 105 (the kit's own refinement and an independent CFG walk agree). Of the refusals below only
`local-rom-halfword-table-v1` reads that count.

## Byte identity

`0801E458.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0801E458, with every callee and data symbol bound to its
ROM address (7 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 244-byte symbol equals the ROM span `[0x0801E458, 0x0801E54C)`:
SHA-256 `24d46a194bd76792cc6e7dc65c9cd3e5a9e49731ae6f42c7b8e2e1c4faed34b9` for both. `.text` is exactly 244 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0801E458.c` and `g_object_08149914`,
`g_object_0814991C`, `g_object_08149924` added to `config/data_symbols.json` (each at the address its name gives): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2`, `named-data-buffer-rom-table-copy-v1` | `buffer callee 0x081443FC: copy helper receives only a destination alias and no stack-passed pointers` |
| `local-rom-halfword-table-v1` | `complete-owner text reachable instruction count differs` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. Those selectors refuse the second copy here (`copy helper receives only a destination alias and
no stack-passed pointers`): at 0x0801E49C R3 holds the destination address as well as R0 (`add r3, sp, #8; mov sl, r3`
at 0x0801E492-0x0801E494, then `mov r0, sl`), so the helper receives two alias registers. Logging the check's
arguments in a scratch run gives R0 alone at the first copy (0x0801E48E), R0 and R3 at the second, and no
pointer-bearing stack word at either. The helper overwrites R3 before it reads it (`adds r3, r1, #0` at 0x08144402).

## Source notes

- `func_08003508((s16)x, layer)` and `func_08003558((s16)y, layer)`: both prototypes take `s16`, so the casts change
  no value. Without them the bytes are the same (same SHA-256) and so are the five refusals above. They should go
  before this ships.
- The three ROM tables are not in `config/data_symbols.json`; the refusal runs add them (above).

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors); shubshub/fftadecomp-kit#200 (comment to be posted)
