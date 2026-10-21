// func_080CBABC - 0x080CBABC, 132 bytes (0x7E code + 2 pad + 4 literal pool)
//
// target bytes (ROM 0x080CBABC..0x080CBB3F):
//   00 b5 00 06 01 0e 07 48 07 4a 80 18 00 78 80 07
//   80 0f 01 28 14 d0 02 28 22 d1 0f 29 08 d8 48 01
//   02 49 29 e0 00 00 00 02 c2 2f 00 00 60 ac 41 08
//   08 1c 10 38 40 01 01 49 1e e0 00 00 60 ae 41 08
//   0f 29 05 d8 48 01 01 49 16 e0 00 00 40 b7 41 08
//   08 1c 10 38 40 01 01 49 0e e0 00 00 40 b9 41 08
//   0f 29 07 d9 08 1c 10 38 40 01 01 49 04 e0 00 00
//   60 a3 41 08 48 01 02 49 40 18 02 bc 08 47 00 00
//   60 a1 41 08
//
// The indexed span (22 bytes, ending at 0x080CBAD2) stops inside the
// function; the body runs to the interworking return at 0x080CBB38 and the
// last literal pool word is at 0x080CBB3C, so the function is 132 bytes.
//
// What it does: it maps a small index to a 32-byte record in one of three
// read-only tables in the cartridge ROM.  Which table is used comes from the
// two low bits of the byte at RAM 0x02002FC2 - the `mode` field of the state
// block that starts at 0x02000000.  The index selects the record: entries
// 0..15 are the first half of the table, entries 16..31 the second half,
// whose base is 0x200 bytes higher, so the address is
//
//     base + (index < 16 ? index : index - 16) * 32
//
// and the callers copy the 32 bytes out of it.
//
// Build notes, all of them load-bearing:
//
//  - The state block is reached through a symbol.  With the literal
//    0x02000000 agbcc folds base and offset into a single pool word
//    (0x02002FC2); through the symbol the two stay apart, which is what the
//    ROM does: `ldr r0,[pc]` / `ldr r2,[pc]` / `adds r0,r0,r2`.
//  - `mode` is a two-bit field, so the byte load is followed by the pair
//    `lsls #30 / lsrs #30` - that pair is the two-bit extraction, not a
//    u8 narrowing.
//  - The offset and the table base are kept apart until the final add.
//    Written as one pointer expression, agbcc folds
//    `base + (index - 16) * 32` into `base + index * 32` with a shifted
//    base; the ROM keeps the subtraction and the 0x200 shift apart.
//  - The switch arms are in the ROM's order - case 2 first, then case 1,
//    then the default - and the default arm tests `index >= 16` where the
//    other two test `index <= 15`.  That is what fixes the block layout:
//    case 2 falls through the dispatch, case 1 and the default sit further
//    out, and the default's low-index half ends up next to the shared add.
//  - The record address is `offset + base`, offset first.  The ROM's add is
//    `adds r0,r0,r1` with the offset in r0 and the base in r1.

#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x2FC2];
    unsigned mode : 2;
} State02000000;

extern State02000000 g_state_02000000;

u8 *func_080CBABC(u32 index)
{
    u8 idx = index;
    u32 mode = g_state_02000000.mode;
    u32 offset;
    u32 base;

    switch (mode) {
    case 2:
        if (idx <= 15) {
            offset = idx * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841AC60;
        } else {
            offset = (idx - 16) * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841AE60;
        }
        break;
    case 1:
        if (idx <= 15) {
            offset = idx * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841B740;
        } else {
            offset = (idx - 16) * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841B940;
        }
        break;
    default:
        if (idx >= 16) {
            offset = (idx - 16) * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841A360;
        } else {
            offset = idx * 32;
            /* plausible: read-only 32-byte records in the cartridge ROM */
            base = 0x0841A160;
        }
        break;
    }
    return (u8 *)(offset + base);
}
