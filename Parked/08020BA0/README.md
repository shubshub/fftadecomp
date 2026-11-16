# 0x08020BA0 - near miss: byte-identical only through a single-use inline helper (512 bytes)

Target: complete `[0x08020BA0, 0x08020DA0)`, 512 bytes, 242 instructions. Default flags; `g_state_0200F1D4` and
`data_040000D4` are already in config/data_symbols.json. Retried 2026-11-16 with kit fcdf2d45.

`08020BA0.c` prints `MATCH - byte identical` (242/242 instructions, 512/512 bytes, elf-symbol-thumb-frame-data-v1) and
`plausible.py --strict` exits 0, through `static inline void copy_rows(const u8 *source, u8 *destination, u16 width,
u16 rows)`, expanded once.

Not shipped: a helper ships only with shared text (the same text reproduces a second function) or as a verbatim copy
of a real ROM function, and `copy_rows` is neither.
- No out-of-line copy: the word 0x040000D4 occurs 13 times in the ROM, 11 in eight functions (080023EC x2, 08002480 x2,
  08003410, 08020BA0 x2, 08135984, 08135B40, 0813BDD0, 0814011C) and 2 in data; only this function loops over it.
- No shared text: the neighbour func_080207F4 (Parked/080207F4, byte-identical but refused by the verifier,
  `local stack pointer escapes through a return register`) expands a row copy of the same shape twice, with the same
  parameter order and `u16 width, u16 rows`, but its text differs (DMA0, `u16` elements, strides 64/32). One generic
  helper shared by both makes this function 508 bytes. func_0801AF08 (not matched) holds six more DMA0 row copies of
  the same shape.
- The only helper-free source that matches needs three single-use locals (below), which exist only to supply fresh
  pseudos.

## What the function does
Runs the queued transfers of the four slots at g_state_0200F1D4 whose kind equals the argument and returns the bytes
moved as u16. A slot moves at most chunk_size bytes a call, or all of size when chunk_size is 0. Kind 0: one 32-bit
DMA3 copy. Kind 1: a 16-bit DMA3 copy per row of width halfwords, the destination advancing 128 bytes a row. Only
caller: func_0801AC78 (bl at 0x0801AC92 with kind 1, 0x0801ACDA with kind 0); both discard the result.

## What the helper reproduces (0x08020CB4..0x08020CC4)
1. Width changes type: the row copy works on a copy of the width (`ldr r6, [sp, #4]` at 0x08020CB4); with the width
   used directly, or copied to an object of its own type, the frame is 0x10 instead of the ROM's 0x14 (0x08020BAA)
   and the function is 508 bytes.
2. The u8 truncation of rows is split: `lsls r0, r1, #0x18` at 0x08020CB8, then the source (0x08020CBA) and
   destination (0x08020CBE) loads, then `lsrs r0, r0, #0x18` at 0x08020CC0.
3. The row count is not u8: it sits in r8 before `row = 0` (0x08020CC2, 0x08020CC4) and both tests use r8 (0x08020CD0,
   0x08020D10). A u8 count tests r0 and adds `mov r8, r0` after the entry test (222/242).
The initial RTL of the helper form evaluates all four arguments (insns 283..297) and then copies them to the
parameters in order (299..305); the loads and the `lsrs` end up at the copies, the `lsls` where the argument was
evaluated. The `(u8)` at the call is the ROM's truncation at 0x08020CB8/0x08020CC0.

## The helper-free match
In place of the call:

        {
            u16 row_width = width;
            u8 height = rows;
            const u8 *source = slot->current_source;
            u8 *destination = slot->current_destination;
            u16 row_count = height;
            u16 row;

            for (row = 0; row < row_count; row++)
            {
                /* plausible: DMA3 MMIO requires word writes, control readback and completion polling. */
                volatile DmaRegisters08020BA0 *dma = &data_040000D4;
                dma->source = source;
                dma->destination = destination;
                dma->control = 0x80000000 | row_width;
                (void)dma->control;
                while (dma->control & 0x80000000)
                    ;
                source += row_width * 2;
                destination += 128;
            }
        }

`rows` is a 32-bit local (the quotient is stored untruncated at 0x08020C2A and 0x08020C5E and used untruncated at
0x08020D74; `u8 rows` is 508 bytes, `u16 rows` 520) and nothing is read from a u8 object at that point, so `height`
is a single-use u8 local, `row_count` a single-use copy of it and `row_width` a single-use retyped copy of width. All
three are needed. Helper-free forms without them are all 508 bytes (a 0x10 frame, the loop index in a callee-saved
register instead of r3 saved around the calls): a DMA3 helper with a full control word; the natural loop with
`u8 height = rows` and width used directly; height declared before the pointers; `u8 height` plus a `u16 count`
copy; `while (row < (u8)rows)`.

## Evidence for the rest of the source
- Kind 0: source load 0x08020C78, destination load 0x08020C7A, register literal 0x08020C7C, stores 0x08020C7E and
  0x08020C80; the declaration order source, destination, dma is that order and is load-bearing (below). The count
  `lsls r0, r7, #0xe; lsrs r0, r0, #0x10` at 0x08020C82 is `amount / 4`.
- Volatile: both uses are `volatile DmaRegisters08020BA0 *dma = &data_040000D4;` with a `plausible:` comment, used only
  as `dma->member`: the hardware exception for a pointer initialised to a symbol mapped into 0x04000000..0x040003FF,
  as in src/08147A44.c, src/08002480.c and src/080023EC.c.
- Slots at state + 4, stride 0x2C: active +0 (ldrb), kind +1 (ldrb), queued +6 (ldrb/strb), size +8 (ldrh),
  chunk_size +0xA (ldrh), elapsed +0xC (ldrh/strh), current_destination +0x1C (ldr/str, advanced in bytes, so
  `u8 *`), current_source +0x20 (ldr/str), layer +0x24 (address only), dimensions[0] +0x25 and dimensions[1] +0x26
  (ldrb). Names follow src/08020A68.c and src/08020E3C.c.
- kind u8 (entry narrowing 0x08020BAC), index u8, amount u16, transferred u16, row u16; `elapsed + amount > size` is
  a signed int compare. Return u16 (`mov r0, sb` at 0x08020D8E; void is 486 bytes). func_0801B888 and func_08020780
  results are narrowed to u8; func_08141870 is `svc #6; bx lr`, func_08141874 `svc #6; adds r0, r1, #0; bx lr`.
  Constants 0x84000000, 0x80000000, 128, 4 slots.

## Alternatives compiled (N/242 identical instructions; "short N" = a symbol of N < 512 bytes)
| form | result |
| --- | --- |
| helper (source, destination, u16 width, u16 rows), `(u8)rows` | MATCH |
| helper (u16 width, source, destination, u16 rows); width u8/u16, rows u16/u32, width anywhere before rows (12 forms); `(u8)width, (u8)rows` | MATCH |
| rows second / first / between the pointers / before width | 230 / 224 / 237 / 238 |
| destination before source | 240 |
| u16 rows without the cast / u32 rows without the cast | 240 / short 504 |
| u8 rows (with or without the cast) | 222 |
| s32 rows / u32 width parameter | 240 / short 508 or 504 |
| `rows & 0xFF` argument; u16 pointers | 516 bytes |
| helper-free with row_width, height, row_count (also with u32 row_count, u8 row_width, or `row_count = height` in the for-init) | MATCH |
| helper-free `u16 row_count = (u8)rows` after / before the pointers | 206 / 197 |
| helper-free `u8 row_count = rows` (the older parked source); cast in the loop condition | 222; 219 |
| helper-free without row_width, or with a u32 one | short 508 |
| helper-free, height before row_width / row_width after the pointers | 238 / 163 of 235 |
| kind 0: direct member writes / source local only / destination local only | 239 / 239 / 240 |
| kind 0: dma declared before the two locals / destination first | 241 / 241 |
| kind 0 count as `amount >> 2` and cast variants | MATCH |
| `amount = chunk_size; if (amount == 0) amount = size;` | short 504 |
| `amount >= slot->size` / `kind == 1` on the parameter | 217 of 243 / 230 of 243 |
| if / else if for the second dispatch | short 510 |
| u32 func_0801B888 | 232 of 239 |

## Notes on other files
- src/0801AC78.c declares `void func_08020BA0(u8 enabled)`; the function returns u16 and the argument is the slot kind.
- src/0801B888.c returns `u32`; this function and src/0801AC78.c narrow the result to u8.
