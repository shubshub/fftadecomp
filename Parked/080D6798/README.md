# 0x080D6798 - clipped tile-block blit from a tile stream: near miss, compiles to 428 of 438 bytes (438 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function writes a `width` x `height` block of tile
entries into a 32 x 32 tilemap at `destination`, starting at `(x, y)`. With `flipX` or `flipY` it walks that
axis backwards from the far edge and XORs the entry with 0x400 or 0x800. Cells whose row or column falls
outside 0..31 are skipped with separate signed tests (`blt`/`bgt` at 0x080D686A-0x080D686E and
0x080D689C-0x080D68A0). Each written cell takes the next value from the matched stream decoder
`func_080D663C(&source, &index, encoded)` (0x080D68B0). When `base` or `palette` is non-zero, a value whose
tile number (low 10 bits) is not 0x3FF gets `base` added to the number and `palette` added to the top
nibble, with the flip bits kept. The matched caller `src/080D6A34.c` calls it with this argument list. The
index row `080D6798 080D694E 438 219 return` has the right extent: 213 reachable instructions (1 `bl`), code to
0x080D694E, literal words at 0x080D68DC and 0x080D68E0. Its count column is the halfword count. No data
symbol is needed.

## Byte identity

`080D6798.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D6798 with `func_080D663C` bound to its ROM
address (1 `R_ARM_THM_CALL`). The symbol and `.text` are 428 bytes, 10 short of the 438-byte span: 208
reachable instructions against the ROM's 213. ROM span SHA-256
`c8d646e7544f27ae358f528a29029530575fcbd88d71f115a988579e09197689`, linked 428-byte symbol SHA-256
`fd653a76cfe9be5cd09e625238f2d8f176287c05f847e8e878533da76399c47f`. The first difference is at 0x080D67A2.

`match.py --root . --no-write 0x080D6798` stops before its byte comparison with `compile failed: buffer caller
requires an exact complete mapped span`. The function passes the addresses of two locals (`&source`,
`&index`) to `func_080D663C`, so it goes through the buffer-caller path. That path compares the 438-byte
mapped span with the 428-byte compiled symbol and stops on the length difference
(`tools/match.py:6045-6046`). `plausible.py --strict` exits 0.

The control flow, the clipping tests, the call and the tile arithmetic have the same shape as the ROM. What
differs is the frame and which values live in registers or on the stack:

- Frame: ROM `sub sp, #72` (0x080D67A2), this build `sub sp, #64`. Every incoming stack argument is
  therefore loaded 8 bytes lower (`ldr rN, [sp, #104]` to `#128` in the ROM at 0x080D67A8-0x080D67B6,
  `#96` to `#120` here), and most spill slots move with it.
- `palette`: the ROM spills it to `[sp, #32]` (0x080D67DC) and reloads it for the adjustment (`ldr r4, [sp,
  #32]`, 0x080D68CA). This build keeps it in sl.
- Per row, the ROM stores the row pointer to `[sp, #52]` (0x080D6876). It puts `(s16)x` in sl (0x080D6888)
  and hoists the 0x3FF mask into sb once (`ldr r0, =0x3FF; mov sb, r0`, 0x080D688A-0x080D688C). This build
  keeps the row pointer in sb, `(s16)x` in r8, and has no hoisted mask.
- Per cell, the ROM keeps the column displacement in r8 (0x080D6898), stores the cell address to `[sp, #68]`
  (0x080D68A8) and reloads it for the store (0x080D6904). This build spills the displacement to
  `[sp, #60]`, keeps the cell address in r4, and loads 0x3FF from the pool inside the adjustment (`ldr r7,
  =0x3FF`).

Those extra stores and reloads and the hoisted mask make up the ROM's 5 extra instructions (10 bytes).

## Cause

The ROM gives the 0x3FF mask and `(s16)x` the high registers for the whole inner loop. It spills `palette`,
the row pointer and the cell address. agbcc on this source keeps `palette`, the row pointer and the cell
address in registers instead, spills the column displacement and reloads the mask for each cell. Its frame
needs two fewer spill words. As a diagnostic only (flags are fixed at `-O2`), compiling this source with
`-fno-cse-skip-blocks` gives a 434-byte symbol with a 68-byte frame. CSE across the jump over the
`base`/`palette` test therefore affects the allocation, but that flag does not reproduce the ROM either. No
source form tried so far gives the 72-byte frame.

## Source notes

- `adjust_tile` is a `static inline` helper that does a real operation (the tile-number and palette
  adjustment), which AGENTS.md accepts for a helper. No matched sibling shares its text, so there is nothing
  to cite for it. It is not neutral: writing the same operations out in place (with `if (number != 0x3FF)`
  instead of the early return) gives a 416-byte symbol.
- The bank is spelled `(tile & 0xF000) >> 12`. A plain `tile >> 12` also gives 428 bytes but is further from
  the ROM (258 differing byte positions against 219).
- `x`/`y` are `s16`, and the displacements are `s16` locals stepped by `dx`/`dy`. `base` is `u16`, as the
  caller `src/080D6A34.c` declares it.
- The source pointer is `const u16 *`, matching the matched decoder `src/080D663C.c` (`const u16 **stream`).
  The caller `src/080D6A34.c` declares this parameter `const u8 *data` and passes the pattern's byte data.
  One of the two declarations is wrong, and the bytes here do not show which.
- The parameter order and names follow the caller's declaration (`flipX`, `flipY`, and a last `u8` that the
  caller fills with `pattern->flags & 2` and this function passes on as `encoded`).

## Ruled out

- The previous parked copy (main) used `u16` coordinates with `(s16)` casts, one combined `< 0 || > 31` test
  per axis, and the adjustment written inline. It compiles to a 372-byte symbol with a 52-byte frame, and
  `match.py` stops with the same `buffer caller requires an exact complete mapped span`. This source changes
  those to `s16` coordinates, a `u16` base, split signed bound tests and the cell address formed before the
  call, which brings it to 428 bytes and a 64-byte frame.
- The adjustment written out in place instead of `adjust_tile`: 416 bytes.
- `bank = tile >> 12` instead of the masked form: 428 bytes, further from the ROM (above).
- `-fno-cse-skip-blocks` (diagnostic, not a usable flag): 434 bytes and a 68-byte frame, with either spelling
  of the bank.

kit issue: none (not byte-identical)
