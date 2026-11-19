# 0x080DB00C - sprite-to-background conversion task: bytes identical, refused (a local initialised table copied by `ldm`/`stm` and indexed by a variable, beside a CpuSet callee) (1332 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u32 func_080DB00C(void *task, BackgroundTask *control, BackgroundState *state)` is a background task callback;
`func_080DB540` starts it through `func_08005B6C` with a 0x1118-byte state.

| Phase | Address | What it does |
|---|---|---|
| 0 | 0x080DB06C | Copies a 0x14-byte parameter block field by field, sets the map origin to column 2, row 7, and optionally calls `func_080DE33C`. |
| 0x100 | 0x080DB0C4 | Waits for `func_080DE488` when that flag is set, then reads 0xC0 words of 4bpp tiles from OBJ VRAM (0x06010000 + tile*32) into state+0x14. |
| 0x101 | 0x080DB108 | Converts the tiles into state+0x314: 4bpp with a fill colour for transparent nibbles, or 8bpp in a palette bank with optional h-mirroring. |
| 0x102 | 0x080DB226 | Clears the map at state+0x914, then walks the sprite frame's packed OAM cells to build a text map (u16) or an affine map (u8). |
| 0x103 | 0x080DB4C0 | Uploads the tiles. |
| 0x104 | 0x080DB4DE | Uploads the map. |
| 0x105 | 0x080DB500 | Copies the sprite's OBJ palette row into the BG palette row, then sets the phase to 2. |

## The index

The index row `080DB00C 080DB540 1332 592 return` is right: the start is word aligned, the epilogue fits the
prologue, and the last pool words are 0x080DB538 and 0x080DB53C. The kit's `analyze.refine_function` closes the CFG
with 592 reachable instructions.

## Byte identity

`080DB00C.c` (SHA-256 `59f553d65e6fabb564352d6e8d1faf0f89f918de953b69b78f46257331c38fd6`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x080DB00C, with every callee and data symbol bound to its ROM address (15 `R_ARM_THM_CALL`,
2 `R_ARM_ABS32`) and the object's `.rodata` placed at 0x08149B34. The 1332-byte symbol equals the ROM span
`[0x080DB00C, 0x080DB540)`: SHA-256 `5836e79f67831c81d7baaeb39b61b5e9620bdec493315abd2c099937be57ec9f` for both.
`.text` is exactly 1332 bytes. The 48-byte `.rodata` initialiser equals the ROM at 0x08149B34
(`01 01 00 00 02 02 00 00 04 04 00 00 08 08 00 00 / 02 01 00 00 04 01 00 00 04 02 00 00 08 04 00 00 /
01 02 00 00 01 04 00 00 02 04 00 00 04 08 00 00`). `.data` and `.bss` are empty. `match.py` refuses before its own
byte comparison (below). `plausible.py --strict` exits 0.

The two literal words are `+0x270 R_ARM_ABS32 .rodata+0` (ROM word 0x08149B34) and `+0x52C R_ARM_ABS32
data_03003860` with in-place addend 0x200 (ROM word 0x03003A60). The 15 calls are, by offset, `+0A8 func_080DE33C,
+0C0 func_080DE488, +0CE func_080DBD48, +0D8 func_080D3AF8, +0EA func_08000ADC, +104 func_080DBD30, +240
func_080DBD30, +260 func_0814186C, +292 func_0814186C, +4B4 func_080D3AF8, +4C4 func_08000ADC, +4D2 func_080D3AF8,
+4E0 func_08000A98, +4F6 func_08099C10, +50E func_0814186C`. A hand link that defines the callees as plain
linker-script symbols gives a 1404-byte `.text`, because `ld` adds interworking veneers for untyped absolute
symbols; defining them as Thumb functions avoids that.

## Data symbols

None needed: the source uses the existing `data_03003860` with addend 0x200.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/080DB00C.c`. None matched.

| Selector | Refusal |
|---|---|
| default | `unexpected nonempty allocated section` |
| `--owner-runtime-profile named-data-buffer-rom-table-copy-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--owner-runtime-profile named-data-buffer-stack-index-v2` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--owner-runtime-profile bounded-buffer-bios-fill-source-v1` | `unexpected nonempty allocated section` |
| `--owner-runtime-profile bounded-buffer-bios-fill-local-source-semantics-v1` | `unexpected nonempty allocated section` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `unexpected nonempty allocated section` |

`unexpected nonempty allocated section` is raised by `match.py`'s `allocated_text_only` (line 633 at b141ba59). The
only profile that admits a `.rodata` initialiser is `rom_table_copy_profile.py`, which models the copy as a call to
the `memcpy` helper `func_081443FC` with a constant count of 1 to 15 and refuses variable indexing of the copy.

## Cause

The owner frame is 0x64 bytes. Case 0x102 holds all of the following together:

- **A compiler `.rodata` initialiser copied inline.** `SpriteSize sizes[3][4]` is a 48-byte, word-aligned array of
  `{u8 width, height}` padded to 4 bytes. agbcc copies it with the movstr expansion, not with `memcpy`:
  `add r6, sp, #4; adds r1, r6, #0; ldr r0, =.rodata` (0x080DB22A..0x080DB22E), then four
  `ldm r0!, {r2, r3, r4}; stm r1!, {r2, r3, r4}` (0x080DB230..0x080DB23E). The destination is sp+4..sp+0x33.
- **A variable index into that copy.** The index is `shape*16 + size*4` (+0 for width, +1 for height). The base sp+4
  lives in r6 and is spilled to `[sp, #0x4C]` at 0x080DB2C0; it is read at 0x080DB2E8 (`ldrb r1, [r1]`) and
  0x080DB2F8 (`ldrb r3, [r3, #1]`).
- **Stack outputs to a callee.** `func_080DBD30` receives &hflip and &vflip (sp+0x34, sp+0x35) at 0x080DB24C; case
  0x101 also calls it at 0x080DB110 with sp+0 and sp+1.
- **CpuSet fills through `func_0814186C` with a stack source halfword.** The text fill uses sp+0x36 with control
  0x01000400 and calls at 0x080DB26C; the affine fill uses sp+0x38 with control 0x01000400 and calls at 0x080DB29E.
  Case 0x105 also uses `func_0814186C` to copy 16 halfwords (0x080DB51A).
- **Spilled pointer and scalar locals in a triple loop**, at sp+0x3C..0x60: control, frame, map, base, the table
  base, height, i<<16, the attr1 high byte, a shared spill slot, and row.

A note for a future index premise: `shape` is OAM attr0 bits 14-15 and `size` is attr1 bits 14-15, both 0..3 as
2-bit fields, but the table has only 3 shape rows (GBATEK lists shape 3 as prohibited). A cell with shape 3 would
read offsets 48..61, past the copy and into hflip, vflip, the fill halfwords and the control spill at sp+0x34..0x3F.
A premise that a cell's shape is at most 2 bounds the index to 0..47. No such data was looked for, and nothing here
claims that it occurs.

### The named-table alternative (not used)

`080D9350` copies a ROM table to the stack from a named symbol (`LineScrollRegisters registers = data_08149B14;`).
The same could be written here:

```c
typedef struct { SpriteSize size[3][4]; } SpriteSizeTable;
extern const SpriteSizeTable data_08149B34;
SpriteSizeTable sizes = data_08149B34;
```

That would replace the `.rodata` relocation with a named-data one and would need `data_08149B34` in
`config/data_symbols.json`. This form was not compiled; the same instructions are expected (a 48-byte word-aligned
struct copy uses the same `ldm`/`stm` expansion), but that is unverified. It is not used, for three reasons:

1. **The `.rodata` layout points to a local initialised array.** The constants near this address follow function
   order, one function's local initialisers after another: 0x08149B14 (080D9350), 0x08149B34 (this function),
   0x08149B64 and 0x08149B68 (080DB540's `u8[4]` and `u16[4]` `memcpy` initialisers), 0x08149B70 (080DE33C),
   0x08149B74 (080DE9E0), 0x08149B88 (080DFCAC). The OAM size table is what a developer would write as a local
   initialised array; a struct wrapper whose only job is to make an array assignable is not.
2. **Rewriting the C to dodge a refusal is steering.**
3. **It would still be refused.** The named form leaves the `func_0814186C` CpuSet callee and the variable stack
   index unchanged, so those refusals remain.

## Source notes

Every item below is load-bearing; each lists the ROM evidence and the plain form that was compiled ("full function"
or "isolated test").

### 1. Dead assignments in the zero arms of the 8bpp loop (unresolved; see "For the reviewer")

The parked source (case 0x101, the 8bpp branch, both nibbles):

```c
pixel = *source & 0x0F;
if (pixel == 0)
    pixel = state->parameters.fill;
else
    destination[x] = pixel | (state->parameters.palette << 4);
...
pixel = *source >> 4;
if (pixel == 0)
    pixel = state->parameters.fill;
else
    destination[x] = pixel | (state->parameters.palette << 4);
```

The assignment `pixel = state->parameters.fill` is dead: nothing reads it, and flow deletes it. The ROM, high
nibble:

```
080DB1C6  ldrb r0, [r5]
080DB1C8  lsrs r3, r0, #4
080DB1CA  cmp  r3, #0
080DB1CC  bne  0x080DB1D2
080DB1CE  lsls r2, r2, #16      <- zero arm
080DB1D0  b    0x080DB1E0       <- zero arm
080DB1D2  lsls r2, r2, #16      <- draw arm
080DB1D4  asrs r1, r2, #16
...
080DB1DE  strb r3, [r1]
080DB1E0  mov  r1, r8           <- step code; uses r2 = x << 16
```

The low nibble has no such block: `beq 0x080DB1A4` at 0x080DB194 skips the draw.

0x080DB1CE..0x080DB1D0 is a block of its own on the zero path. It holds a gcse/PRE insertion of `x << 16` and a jump
to the join. agbcc's PRE (`gcse.c` `pre_insert`) inserts only at the end of existing blocks and does not split
edges, so this block exists only if the source has a statement on the zero path that is still there when gcse runs.
After gcse, flow deletes the statement and only the insertion remains. Because of the insertion, the step code at
0x080DB1E0 reads `x << 16` from r2, and both arms of the step (0x080DB1EA `adds r0, r2, r3` and 0x080DB200
`adds r0, r2, r1`) use it without recomputing it.

The zero arm's statement must be written first (`if (pixel == 0) A else draw`, laid out as `bne draw; A; b join;
draw:`), and must survive jump1; CSE (which knows `pixel == 0` on that fall-through, so `pixel = 0` is folded away
as a no-op); `delete_trivially_dead_insns` (so the register must have other uses); and the jump pass after CSE.

Spellings that give the ROM bytes (all compiled in the full function, all byte-identical):

- (a) both nibbles `if (pixel == 0) pixel = state->parameters.fill; else draw;` (the parked source);
- (b) only the high nibble in that form, the low nibble a plain `if (pixel) draw;`;
- (c) only the high nibble as `if (!pixel) pixel = 1; else draw;`.

In form (a) the low-nibble zero arm leaves nothing in the ROM: it gets no PRE insertion, and jump2 removes the emptied
block.

Spellings that do not:

| Spelling | Where tested | Result |
|---|---|---|
| plain `if (pixel) draw;` for both nibbles | full function, several times | PRE inserts at the end of the test block: `lsrs r2, r0, #4; lsls r3, r3, #16; cmp r2, #0; beq` (2 fewer instructions). The whole 8bpp loop's allocation flips (x in r3 instead of r2, pixel in r2 instead of r3). Downstream, case 0x101's tail is cross-jumped into case 0x102's, and `map = 0` is stored through r4 instead of r0. |
| `if (pixel == 0) pixel = 0; else draw;` | isolated test | CSE folds it; no block. |
| `if (pixel) draw; else pixel = 1;` (draw arm first) | isolated test | layout `beq A; draw; b join; A: lsls`, the wrong block order |
| `if (pixel == 0) do { } while (0); else draw;` | isolated test | no block |
| `if (pixel) draw; else do { } while (0);` | isolated test | no block |
| `if ((pixel = *source >> 4) == 0) ; else draw;` | isolated test | no block |
| a ternary statement, or a `goto` around the draw | isolated test | no block |
| an inline helper with an early `return` | isolated test | no block |
| testing `*source & 0xF0` directly | isolated test | no block |
| the step code duplicated into both arms | isolated test | changes the step arithmetic to `subs r0, r3, #1; lsls` |

The fill form is a guess: it mirrors the 4bpp branch, where a transparent nibble takes `state->parameters.fill`. The
ROM records only that a statement existed on the transparent path of the high nibble; what it was cannot be
recovered. No bug is claimed: the 8bpp loop leaves transparent destination bytes unwritten, and that is the ROM's
behaviour under every spelling above.

### 2. One `u8 pixel` shared by both branches of case 0x101

r3 holds the 4bpp output byte (0x080DB132 `ldrb r3, [r5]`, modified at 0x080DB142..0x080DB15C, stored at 0x080DB15E)
and also the 8bpp nibble (0x080DB18E `movs r3, #0xf; ands r3, r0`; 0x080DB1C8 `lsrs r3, r0, #4`). Plain forms
compiled (full function): a separate `u8 value` in the 4bpp loop puts value in r1, a copy in r2 and reloads through
r3 (`ldrb r1, [r5]; adds r2, r1, #0; ...; mov r3, r8`); `u8 value = *source; u8 pixels = value;` misallocates the
same way; `u8 pixels = *source; u8 value = pixels;` gives a three-register shape. One narrow u8 local reused for
unrelated values is an attested period idiom.

### 3. OBJ VRAM written as `(u8 *)0x06010000`, not `data_06010000`

The evidence is the reload register choices. In case 0x100 control is reloaded into r2 after the call (0x080DB0FA
`ldr r2, [sp, #0x3C]`). That happens only if 0x06010000 is an immediate operand of the add, reloaded into r1
(0x080DB0EA `ldr r1, =0x06010000`, literal 0x080DB104), which advances reload's round-robin pointer (`reload1.c`
`allocate_reload_reg`, `last_spill_reg`) to r1. With the symbol, the address becomes a pseudo that local-alloc
places in r1; the round-robin pointer stays at r3 and control reloads into r4. Case 0x100's tail then matches case
0x103's and jump2 cross-jumps them, losing 10 bytes; the constant reloads in case 0x101 also shift (0x314 through r0
instead of r3, the masks through r1..r3 instead of r0..r2). The plain form `data_06010000 + tile * 32` (full
function) shows exactly that difference. This is hardware VRAM, the OBJ character base, not a game object. Siblings
080210E4 and 08021484 spell it `data_06010000`; their ROM shape was not compared. The related constants 0x06008000
and 0x0600C000 in the base computation appear as negated literals, 0xF9FF8000 (0x080DB28C) and 0xF9FF4000
(0x080DB384); no relocation can produce a negated address, so they have to be numbers.

### 4. `s16 i` with `i < sizeof(state->source)` (both loops in case 0x101)

ROM, 4bpp loop at 0x080DB164..0x080DB170 and 8bpp loop at 0x080DB210..0x080DB21C:
`lsls r0, r6, #16; movs r1, #0x80; lsls r1, #9; adds r0, r0, r1; lsrs r6, r0, #16; cmp r6, sb; bls`, with
sb = 0x2FF. `u16 i; i < 0x300` gives `adds r0, r6, #1; lsls; lsrs; cmp; bls` (full function); `s16 i; i < 0x300`
gives a signed `asrs; cmp; ble` (isolated test). Only an s16 counter against an unsigned bound gives both features;
`(u16)i < 0x300` and `i < 0x300u` work too (isolated tests). `sizeof` is the natural spelling.

### 5. `s16 width, height` for the size-table bytes (case 0x102)

Width is loaded at 0x080DB2E8 (`ldrb r1, [r1]`) and kept in ip (0x080DB2EA `mov ip, r1`); height at 0x080DB2F8
(`ldrb r3, [r3, #1]`). After the row loop's entry test the preheader copies both (0x080DB310 `mov sl, ip`,
0x080DB312 `str r3, [sp, #0x50]`): loop-hoisted sign extensions. Plain forms compiled (full function): `u8` puts the
`ldrb` straight into sl and stores height at once, with no copies; `u16` and `s32` behave as `u8`; `u32` also turns
`blt` into `blo`. The bounds are typed like the s16 loop counters x and y; the loads are `ldrb` of u8 table fields,
so the local type is wider than the load.

### 6. `left = -left; left -= 8;` and `top = -top; top -= 8;` (flipped cell position)

ROM: x at 0x080DB354..0x080DB35E, `lsls r0, r1, #16; rsbs r0, r0, #0; asrs r0, r0, #16; subs r0, #8; lsls; lsrs`; y at
0x080DB3C6..0x080DB3D0, the same. The negation is truncated to 16 bits before the subtraction. `left = -left - 8`
gives `lsls; asrs; rsbs; subs`, sign-extending before negating (full function and isolated); `(s16)-left - 8` is the
same as the plain form (isolated); `-(left + 8)` gives `adds #8; rsbs` (isolated).

### 7. `column += hflip ? -x : x;` and `row += vflip ? -y : y;`

Column (0x080DB36A..0x080DB39C): each arm sign-extends x (`lsls r1, r3, #16; asrs r0, r1, #16; subs r0, r4, r0`,
with `adds` in the other arm), there is one truncation at the join (0x080DB396/0x080DB398), and `x << 16` is kept in
ip for the loop increment (0x080DB39A `mov ip, r1`). Row (0x080DB3DC..0x080DB3F8) is the same, with the
sign-extended y hoisted to r8 (0x080DB320/0x080DB322). `column = hflip ? column - x : column + x` (full function) and
if/else statements (isolated) both narrow the arithmetic to 16 bits and drop the sign extension
(`mov r1, ip; subs r0, r4, r1`).

### 8. `entry = tile + base; entry |= palette << 12;`

ROM (0x080DB400..0x080DB40C): `ldr r3, [sp, #0x48]; adds r0, r5, r3; lsls r0, #16; ldrb r1, [r7, #6]; lsls r1, #28;
orrs r1, r0; lsrs r1, #16`. The plain `(tile + base) | (palette << 12)` (full function) gives
`adds; ldrb; lsls #12; orrs; lsls #16; lsrs #16`.

### 9. The `CPU_FILL16` statement macro, spelled through a pointer

ROM, text fill (0x080DB25E..0x080DB26C): `mov r0, sp; adds r0, #0x36; ldr r2, =0x3FF; adds r1, r2, #0; strh r1, [r0];
ldr r2, =0x01000400; ldr r1, [sp, #0x44]; bl`. Affine fill (0x080DB290..0x080DB29E): `add r0, sp, #0x38;
ldr r4, =0xFFFF; adds r1, r4, #0; strh r1, [r0]; ldr r2, =0x914; adds r1, r7, r2; ldr r2, =0x01000400; bl`. The
register copy before `strh` belongs to the SDK's `vu16` temporary; the two slots (0x36 and 0x38) are two
block-scoped temporaries, one per expansion; the `map` store (0x080DB258..0x080DB25C) comes before the fill, so the
temporary is declared in a block after that assignment. A non-volatile `u16 fill; fill = 0x3FF;
func_0814186C(&fill, ...)` (full function) stores with `ldr r1; strh r1` and no copy. In isolation the pointer
spelling and `volatile u16` give the same bytes; the `volatile` spelling would need a per-file kit qualifier module
(kit #164 is still open). `src/0802C034.c` and `src/08068620.c` use the same pointer spelling.

### 10. Packed u16 bit-field OAM cells: `SpriteCell` and `SpriteFrame`

| Field | Addresses | Code |
|---|---|---|
| shape, size | 0x080DB2D2..0x080DB2F8 | `ldrb; lsls #24; lsrs #30`; the `lsls` is shared and the `lsrs` repeated for width and height |
| tile | 0x080DB2FA..0x080DB304 | `ldrb [#4]; ldrb [#5]; movs #3; ands; lsls #8; orrs` |
| x | 0x080DB32A..0x080DB334 | `ldrb [#2]; ldrb [#3]; movs #1; ands; lsls #8; orrs` |
| hflip, vflip | 0x080DB40E..0x080DB436 | `lsls #27; lsrs #31` and `lsls #26; lsrs #31` from one byte |
| count | 0x080DB2B0..0x080DB2B8 and 0x080DB4A4..0x080DB4AC | `ldrb; ldrb; lsls #8; orrs` |

The cells are 6 bytes apart, after the 2-byte count. Plain forms (isolated tests): byte arithmetic `p[3] >> 6` gives
`lsrs #6` and lets CSE share the whole index; u8 bit-fields give an 8-byte struct (the wrong stride) and
`lsls #30; lsrs #22` for the 2-bit tile_high; packed u16 bit-fields give every pattern in the table with a 6-byte
stride. There is precedent for `__attribute__((packed))` in `src/080D2AD0.c`. Field names follow GBATEK's OAM
attribute layout; `unknown_2` covers attr1 bits 9-11.

### 11. `u16 *map = 0;` (case 0x102)

The ROM stores the 0 at 0x080DB226 (`movs r0, #0`) and 0x080DB228 (`str r0, [sp, #0x44]`); the affine path never
reads `map`. A version without the initialiser was not compiled: nothing else in the source would produce this
store.

### 12. Separate `left` and `top` locals

With one `position` variable reused for x and y (full function), the y half swaps r1 and r2: the ROM has
`ldrb r2, [r6]; adds r1, r2, #0` at 0x080DB3A4, the reused-variable build `ldrb r1, [r6]; adds r2, r1, #0`.

### 13. Declaration order: `frame` before `map` in case 0x102

This puts the spill slots at sp+0x40 for `frame` (0x080DB250) and sp+0x44 for `map`; the reverse order swaps the
slots (full function). The order is load-bearing.

### 14. `data_03003860` declared as `PaletteBuffer { u16 bg[16][16]; u16 obj[16][16]; }` (case 0x105)

One literal serves both palette rows: 0x080DB50A `ldr r2, =0x03003A60` (literal 0x080DB538); the BG row is reached by
adding -0x200 (0x080DB512 `ldr r3, =0xFFFFFE00; adds r2, r2, r3`, literal 0x080DB53C), CSE's related-value reuse.
Two separate symbols would give two literals. The relocation is `data_03003860+0x200`, on an existing symbol.
`data_03003A60` with a negative index gives the same bytes; the struct reads as the BG+OBJ palette buffer.

### 15. Field-by-field parameter copy in case 0

0x080DB06C..0x080DB092 copies word 0, bytes 4..9 one at a time, then words 0xC and 0x10. A struct assignment would
copy with `ldm`/`stm`; that form was not compiled.

### 16. The 4bpp tests read `*source`

The source is `pixel = *source; if ((*source & 0x0F) == 0) ...; if ((*source & 0xF0) == 0) ...`. In the ROM the
loaded byte (r3) is the value that gets modified, and a copy (r1, made at 0x080DB134) feeds the second test: CSE
turns the first test's `*source` into the loaded register, and gcse gives the second test the copy. The other
spellings are listed in note 2.

### 17. Smaller items

The return value of `func_080DBD30` is discarded in case 0x101. `case 1: break;` and `return 0` follow sibling
080DAE7C.

## For the reviewer

Note 1 is unresolved. The ROM contains the zero-arm block at 0x080DB1CE..0x080DB1D0, and no source without a
statement on the high nibble's zero path reproduces it. The statement itself leaves no instruction in the ROM, and
its content cannot be recovered: spellings (a), (b) and (c) are all byte-identical. Two readings follow:

- **It ships.** The arm is physically in the ROM, so a zero-first arm with a dead assignment ships with the address
  comment the source already carries.
- **It does not ship.** The assignment leaves nothing in the ROM and only shapes the code.

This needs a maintainer ruling, together with a choice among (a), (b) and (c). The parked source uses (a); its
comment cites 0x080DB1CE..0x080DB1D0 and says the assignments are dead.

kit issue: none filed yet (a compiler `.rodata` initialiser copied inline by `ldm`/`stm` and indexed by a variable, beside a CpuSet wrapper callee)
