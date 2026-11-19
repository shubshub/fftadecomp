# 0x0801AF08 - map window copy to two screen blocks: bytes identical, refused (a stack fill halfword's address stored to the DMA0 source register) (1740 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_0801AF08(State0801AF08 *state, u8 *first, u8 *second, u16 *buffer, u16 *secondary_buffer, u8 use_dma)` is
reached only through `func_0801B7F8`, called from `func_0801AC78`, which passes `g_state_02007F40`, its two screen-block
pointers at +0x14 and +0x18, `data_020091A0` and `data_020091A0 + 0x2000`, and 1.

1. It measures how far the scroll position (+0x28 x, +0x2A y, both `s16`) runs past the map edges (+0x08 width,
   +0x0A height, in pixels). Each overhanging side sets one bit in `edges`: 1 left, 2 right, 4 top, 8 bottom.
2. If any edge overhangs, it fills both screen blocks (when `func_0801E648` / `func_0801E658` report the layer
   enabled) with the fill tile (+0x1E); the byte size is at +0x06. It fills by DMA0 with a fixed source, or by BIOS
   CpuSet fill, as `use_dma` says.
3. It returns early if the overhang exceeds the map size.
4. Otherwise it copies the visible window of each 64-tile-wide map buffer, one row at a time, to its 32x32 screen
   block, by DMA0 or by CpuSet. A map 256 pixels wide needs one copy; a wider map needs two, the columns from 32
   onwards going to the second screen block, 0x800 bytes further on.
5. It clears bit 0 of the state flags (+0x2C).

No bug is claimed. The early returns at 0x0801B07E and 0x0801B08A skip the flags clear at 0x0801B5B6; whether that was
intended cannot be told, so there is no `BUG` comment.

## The index

The index row `0801AF08 0801B5D4 1740 826 return` is right: the start is word aligned, the prologue
(`push {r4-r7, lr}; push {r8-r10}; sub sp, #0x2c`) matches the epilogue, and the function ends with the literal
0x0000FFFE at 0x0801B5D0. The kit's `analyze.refine_function` closes the CFG with 826 reachable instructions.

## Byte identity

`0801AF08.c` (SHA-256 `f45ad6e89378db52e4134a4237ca5cfa675031bdb02bfb8528575cc2b94cb089`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0801AF08, with every callee and data symbol bound to its ROM address (16 `R_ARM_THM_CALL` to
`func_0801E648`, `func_0801E658` and `func_0814186C`; 8 `R_ARM_ABS32` to `data_040000B0`). The 1740-byte symbol
equals the ROM span `[0x0801AF08, 0x0801B5D4)`: SHA-256
`1e14a6ded2344fe0e6d0d5d633164f08bd8f941f695a51c655efab14f4bba47f` for both. `.text` is exactly 1740 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: `data_040000B0` is already in `config/data_symbols.json`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0801AF08.c`. None matched.

| Selector | Refusal |
|---|---|
| default | `unsupported stack-alias use or escape` |
| `--owner-runtime-profile immediate-dma-stack-fill-v1` | `immediate DMA fill: exactly one local MMIO qualifier must be present after preprocessing` |
| `--owner-runtime-profile bounded-buffer-bios-fill-source-v1` | `unsupported stack-alias use or escape` (the same site, 0x0801AFCE) |
| `--owner-runtime-profile bounded-buffer-bios-fill-local-source-semantics-v1` | `unsupported stack-alias use or escape` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `unsupported stack-alias use or escape` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-scalar-control-data-v1` | `unsupported stack-alias use or escape` |

The message is raised at `tools/match.py:5238` (`verify_leaf_instructions`), at 0x0801AFCE `str r0, [r1]`, with the
walk's alias map `r0: entry SP - 76`. `immediate-dma-stack-fill-v1` counts four MMIO qualifiers after preprocessing
(`DMA0_TRANSFER` has two blocks and is used in two helpers); even with one qualifier, that selector covers a narrower
shape (one fill, no loops, no CpuSet). The C was not reshaped to get past any refusal.

## Cause

At 0x0801AFCE, `r0 = sp` holds the address of the fill halfword (`u16 fill` at sp+0, stored at 0x0801AFCA), and it is
written to DMA0SAD (`r1 = 0x040000B0`). This is the shape of the open kit #239 (an immediate DMA fill whose fixed
source is a local word is refused as a stack-alias escape; 08003410, 0814011C, 08135B40, 0813BDD0). This owner also
has:

- a fixed 0x2C-byte frame with ten spilled words;
- two incoming stack arguments: `secondary_buffer` at sp+0x4C and the `u8 use_dma` at sp+0x50;
- BIOS CpuSet fills (`func_0814186C`, bit 24 set) from the same stack halfword, at 0x0801B00E and 0x0801B06E;
- six DMA0 row loops (16-bit, incrementing, with a control readback and a completion poll) and six CpuSet row-copy
  loops from external buffers (bit 24 clear).

## How the last difference was closed

1. Direct C with `u16` coordinate fields: the 0xFFFFFE00 constant came out as `movs #0xFE; lsls #8`. Making the `x`
   / `y` fields and `dx` / `dy` `s16` fixed the edge code: agbcc's Thumb `PROMOTE_MODE` keeps every narrow local
   zero-extended, so an `s16` local is still stored with `lsrs #16` and sign-extended again at each use, exactly as
   the ROM does. `x + (width - 0x200)` with an `s16` operand narrows to signed short arithmetic and keeps -512 as a
   pool word.
2. Direct fill code loaded the fill size after storing the fill tile. The ROM loads both first, so the fills became
   inline helpers (arguments are evaluated before the body). The two-block DMA form (write and read back, then wait)
   matched the fill; one block swaps r1 and r2.
3. With the row copies as inline helpers, everything matched except two of the six DMA0 row loops: layer 1 of the
   256-wide copy, around 0x0801B1DE, and layer 1 of the second screen-block copy, around 0x0801B546. The output was
   1732 bytes against 1740.

The cause of that last difference, from the `-dG`, `-dl` and `-dg` dumps:

- gcse PRE moves each DMA loop's three increments (`source + 128`, `destination + 64`, `i + 1`) ahead of the
  completion poll. That is why the ROM shows `adds r3, #0x80; adds r1, #0x40; adds r5, r2, #1` between the `ands` and
  the `beq`.
- PRE creates one new pseudo for each increment, in expression-hash-bucket order. For `(plus (reg r) (const_int c))`
  the bucket is `(13772 + r + c) mod T`, where 13772 = PLUS 70 + SImode 6 + (CONST_INT 51 + REG 56) * 128 and
  T = n_insns/2 | 1 = 371.
- These pseudos then tie in global-alloc priority (refs 4, live 11), so the lower pseudo number takes the lower
  register.
- The three operands are consecutive pseudos `s`, `s+1`, `s+2`, so each loop's hash order depends only on
  `x = (13772 + s) mod T`: `ids` when there is no wrap; `dsi` when x lies in [T-65, T-4]; `sid` when x lies in
  [T-128, T-66].
- The ROM needs dsi / ids / ids / ids / sid / dsi for the six DMA loops in order. The near miss had s = 285, 318,
  440, 473, 592, 625, giving dsi / dsi / ids / ids / sid / sid. With T = 371, a uniform shift of +7 to +37 pseudos
  before the first loop gives the ROM's orders for all six.
- A probe (not the parked source) with unused locals confirmed it: shifts of +10 and +20 left only the relocated pool
  words different.
- The parked source gets its +10 from `edges |= 1; edges |= 2;` (see "For the reviewer"). The loops are then at
  s = 295, 328, 450, 483, 602, 635, and the function is identical.

Other variants measured against that diagnosis: making the coordinate locals `s16` changes the code (1764 to 1940
bytes); reordering the fill helper parameters changes nothing; copy helper parameters in the order (destination,
source) change the code (288 diff lines), because the ROM computes the source pointer before the destination pointer
at every site; nested `dma_set` / `dma_wait` inline functions evaluate the control word before the address stores
(1748 bytes); `&value` in place of a `fill` local, and the one-block DMA forms, also break it (T measured 367 or 369,
or the size differed).

## For the reviewer: `edges |= 1; edges |= 2;`

The source writes all four edge flags as ORs:

```c
    u8 edges = 0;
    ...
    dx = -state->x;
    if (dx > 0)
        edges |= 1;
    else {
        dx = state->x + (state->width - 0x200);
        if (dx > 0)
            edges |= 2;
        else
            dx = 0;
    }
    dy = -state->y;
    if (dy > 0)
        edges |= 4;
    else {
        dy = state->y + (state->height - 0x200);
        if (dy > 0)
            edges |= 8;
        else
            dy = 0;
    }
```

(a) The ROM folds the first two to constants: `movs r4, #1; str r4, [sp, #0x1c]` at 0x0801AF38 and
`movs r4, #2; str r4, [sp, #0x1c]` at 0x0801AF54. It keeps the last two as real ORs of the loaded flag word:
`movs r0, #4; ldr r1, [sp, #0x1c]; orrs r1, r0` at 0x0801AF72-0x0801AF76, and `movs r0, #8; ldr r5, [sp, #0x1c];
orrs r5, r0` with the u8 truncation at 0x0801AF90-0x0801AF98.

(b) The 1 and 2 assignments are on mutually exclusive paths: the `if` arm and the `else` arm's inner `if` of the first
statement. Nothing writes `edges` between its initializer `u8 edges = 0;` and either of them, so `edges` is known to
be 0 at both, and `0 | 1` and `0 | 2` fold to the constants. The 4 and 8 assignments are on the two arms of the second
statement; they are reached after the first statement's three paths (`edges` 0, 1 or 2), so they cannot fold.
`edges = 1;` and `edges = 2;` therefore mean the same thing as the ORs.

(c) With `edges = 1;` and `edges = 2;` and everything else unchanged, the function is 1732 bytes, not 1740. The
difference is register allocation in the two DMA0 row loops named above: around 0x0801B1DE, the new source pointer
and the incremented counter swap r5 and r6; around 0x0801B546, the 0x80000000 constant goes to r7 instead of r9, and
the pointers are coalesced differently, which costs four instructions.

(d) The bytes depend on this choice only through pseudo numbering. The two `|=` spellings create 10 more pseudos
before the first row loop; CSE removes the extra instructions before gcse. That moves the gcse PRE hash-bucket order
of the loop increments, and with it the tie-breaks in global-alloc, as explained under "How the last difference was
closed". The spelling leaves nothing else in the ROM.

Text that leaves nothing distinctive in the ROM and only moves registers does not ship. On the other side, a uniform
`|=` style for all four bit flags may well be the most likely original, since the ROM shows the third and fourth as
ORs. The reviewer decides.

## Other source notes

1. **Four `static inline` helpers**: `dma_fill16`, `cpu_fill16`, `dma_copy_rows` and `cpu_copy_rows`. Two statement
   macros, `FILL(destination)` and `COPY_ROWS(source, destination)`, choose between them by `use_dma`.
   - The evidence for functions rather than macros or direct code: each fill loads both arguments, the tile and the
     size, before it stores the tile to the stack (0x0801AFC4 `ldrh r1, [r3, #0x1e]`, 0x0801AFC6
     `ldrh r2, [r3, #6]`, 0x0801AFCA `strh r1, [r0]`; the same at 0x0801AFFA, 0x0801B024 and 0x0801B05A). Written
     directly in the body, the size load comes after the store.
   - The `use_dma` test comes before the loads (0x0801AFBC), so the test is outside the helpers.
   - The CpuSet loops' entry test compares the `use_dma` stack slot (known to be 0 on that path) with the row count
     (0x0801B19A `ldr r0, [sp, #0x14]; cmp r0, r8`); the inline expansion reproduces that.
   - The ROM has each row loop six times and each fill twice.
   - Shared text: the merged `src/08020BA0.c` has `static inline copy_rows` (a DMA3 row loop of the same shape: u16
     counter, readback, poll, pointer steps), and the Parked `080207F4` has the DMA0 version with `source += 64` and
     `destination += 32`.
   - The pointer steps show in the ROM as `adds #0x80` and `adds #0x40`. In this source the destination is `u8 *`,
     because the destination offset is a byte offset (`dst`, a `u16`, added unscaled at 0x0801B146).
2. **`DMA0_TRANSFER` is a statement macro with two blocks**: write the three registers and read the control back,
   then poll in a second block that has its own register pointer. This is the register sequence of the merged
   `src/080012BC.c` `DMA0_COPY32`, and the SDK's DmaSet followed by DmaWait. The ROM has it eight times: the two fills
   at 0x0801AFCC and 0x0801B02C, and the six row loops. With one block, the fill swaps r1 and r2 and the loops change
   (T = 367 or 369). The `volatile` is on the DMA0 register pointer only, with `plausible:` comments as in 080012BC.
3. **Declaration order: `src_x` and `src_y` are declared before `edges`.** The ROM's spill slots show src_y at
   sp+0x18, below edges at 0x1C, dx at 0x20 and dst_y at 0x24; agbcc gives the first-numbered pseudo the lowest slot.
   Declaration order is an allowed lever; it is recorded here.
4. **`dx = state->x + (state->width - 0x200)`** (and the same for y): the ROM computes the constant plus the width
   first, then adds x (0x0801AF3E `ldr r5, =0xFFFFFE00`, then adds at 0x0801AF40, 0x0801AF46 and 0x0801AF48);
   `x + width - 0x200` adds x and the width first. The fields are `s16 x, y`: a `u16` field narrows the sum to
   unsigned short and gives `movs #0xFE; lsls #8` instead of the pool word, and `s16` also fits the
   `lsls #16; asrs #19` at 0x0801B0A8 and 0x0801B0B4.
5. **Section A (the 256-pixel map) stores `dst_x = dx * 2`**: the shift happens at the assignment
   (`lsls r0, r1, #0x11` at 0x0801B0F0), and it sums `dst = dst_x + dst_y * 64` (0x0801B126 `adds r0, r5, r0`).
   Sections B and C store `dst_x = dx` and sum `dst_y * 64 + dst_x * 2` (0x0801B2E6 `lsls r1, r5, #1`, 0x0801B2E8
   `adds r0, r0, r1`). Both forms are read off the ROM.
6. **The wider-map branch recomputes `src_x = state->x >> 3`** (0x0801B27C, after r2 was reused for the constant 32)
   and reassigns `cols = 32` before each half (0x0801B278, 0x0801B410). It sets `rows = 32` at 0x0801B254. All of
   this is read off the ROM.
7. **Types:** `u8 edges` (`lsls/lsrs #24` after `|= 8` at 0x0801AF96); `s16 dx, dy` (stored zero-extended,
   sign-extended again at every use, 0x0801B074, 0x0801B082); `u16` for the width, height, screen size and fill tile
   (`ldrh`, `lsrs #3` at 0x0801B0A0); `u16` for the coordinate, count and index locals (making them signed changes
   the code).

kit issue: shubshub/fftadecomp-kit#239
