// func_080CBA84 - 0x080CBA84, 56 bytes (0x32 code + 2 pad + 4 literal pool)
//
// target bytes (ROM 0x080CBA84..0x080CBABB):
//   00 b5 00 06 01 0e 05 48 05 4a 80 18 00 78 80 07
//   80 0f 02 28 08 d0 48 01 02 49 07 e0 00 00 00 02
//   c2 2f 00 00 60 9f 41 08 48 01 02 49 40 18 02 bc
//   08 47 00 00 60 aa 41 08
//
// The indexed span (22 bytes, ending at 0x080CBA9A) stops inside the
// function; the body runs to the return at 0x080CBAB4 and the last literal
// pool word is at 0x080CBAB8, so the function is 56 bytes.
//
// Address note: the task gave 0x080CAB84, but that address is a literal
// pool word (0x02001940) inside func_080CAB24 - no function can start
// there, and the bytes there cannot be produced by any C.  The function the
// task describes - 22-byte indexed span, 11 caller functions, the same
// 0x080CBxxx table-wrapper module as src/080CB980.c and src/080CB9B0.c - is
// 0x080CBA84, one transposition away.  Its 16 call sites sit in 11 distinct
// caller functions.
//
// What it does: it returns the address of a 32-byte record in one of two
// read-only tables in the cartridge ROM.  Which table is used comes from the
// two low bits of the byte at RAM 0x02002FC2 - the `mode` field of the state
// block that starts at 0x02000000 - and the index selects the record:
//
//     base + index * 32      with base 0x08419F60, or 0x0841AA60 if mode == 2
//
// The callers copy the record out and read halfwords at +0x0E of it.
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
//  - The index is taken wide and narrowed in a local, so the mask lands
//    inside this function: `lsls #24 / lsrs #24` is the u8 narrowing.
//  - The scale by 32 is written in both arms, so the ROM keeps the multiply
//    in each block instead of hoisting it into the join.
//  - The record address is `offset + base`, offset first.  The ROM's add is
//    `adds r0,r0,r1` with the offset in r0 and the base in r1.
//  - The table addresses are plain literals, so each reaches its own use as
//    one pool word (0x08419F60 next to the code, 0x0841AA60 after it).

#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FC2];
    unsigned mode : 2;
} State02000000;

extern State02000000 g_state_02000000;

u8 *func_080CBA84(u32 index)
{
    u8 idx = index;
    u32 mode = g_state_02000000.mode;
    u32 offset;
    u32 base;

    if (mode != 2) {
        offset = idx * 32;
        /* plausible: read-only 32-byte records in the cartridge ROM */
        base = 0x08419F60;
    } else {
        offset = idx * 32;
        /* plausible: read-only 32-byte records in the cartridge ROM */
        base = 0x0841AA60;
    }
    return (u8 *)(offset + base);
}
