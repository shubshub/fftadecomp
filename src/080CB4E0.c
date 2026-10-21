// func_080CB4E0 - 0x080CB4E0, 68 bytes (0x3A code + 2 pad + 8 literal pool)
//
// target bytes (ROM 0x080CB4E0..0x080CB523):
//   00 b5 00 04 00 0c 01 1c 00 28 05 d1 01 48 00 68 11 e0 00 00
//   80 66 52 08 55 28 03 d9 87 21 89 00 40 18 01 e0 05 4a 88 18
//   00 04 01 0c 04 48 09 04 89 13 09 18 08 68 02 bc 08 47 00 00
//   71 02 00 00 80 66 52 08
//
// The indexed span (12 bytes, ending at 0x080CB4EC) stops inside the body;
// the code runs to the interworking return at 0x080CB518, with pool words at
// 0x080CB4F4, 0x080CB51C and 0x080CB520, so the function is 68 bytes.
//
// What it does: it looks a name pointer up in the read-only pointer table at
// 0x08526680.  Index 0 returns the first entry directly; an index of 1..85 is
// offset by 625 and a larger index by 540.  The table index is taken signed
// (s16), so the compiler sign-extends it before scaling it by 4.
//
// Build notes:
//  - The table address has to stay opaque: as a literal constant the compiler
//    folds it into the address arithmetic and picks a different register
//    allocation (the lookup address stays in r0 instead of r1), which does not
//    reproduce the ROM.  As a named global the address is a separate operand
//    and the code matches byte for byte; the two pool entries then carry
//    R_ARM_ABS32 relocations to that symbol.
//  - The index parameter is taken wide and narrowed in a local, so the mask
//    lands inside this function: `lsls #16 / lsrs #16` is the u16 narrowing of
//    the incoming value.

#include "ffta.h"

extern const u32 g_table_08526680[];

u32 func_080CB4E0(u32 value)
{
    u16 index = value;
    u16 offset;

    if (index == 0)
        return g_table_08526680[0];

    if (index > 85)
        offset = index + 540;
    else
        offset = index + 625;

    return g_table_08526680[(s16)offset];
}
