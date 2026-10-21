// func_080CB980 - 0x080CB980, 28 bytes (0x16 code + 2 pad + 4 literal pool)
//
// target bytes (ROM 0x080CB980..0x080CB99B):
//   00 b5 03 1c 0a 04 12 0c 03 48 19 1c 01 23 39 f7 c3 fc
//   01 bc 00 47 00 00 fc 83 3c 08
//
// The indexed span (16 bytes, ending at 0x080CB990) stops before the literal
// pool; the body runs to the interworking return at 0x080CB992 and the pool
// word is at 0x080CB998, so the function is 28 bytes.
//
// What it does: it hands the object and an index to the shared helper
// func_08005318, with the read-only table at 0x083C83FC and a fixed fourth
// argument of 1.
//
// Build notes:
//  - The index parameter is taken wide and narrowed in a local, so the mask
//    lands inside this function: `lsls #16 / lsrs #16` is the u16 narrowing of
//    the incoming value.
//  - The table address is a plain literal, so it reaches the call as one
//    pool entry (0x083C83FC) next to the code.

#include "ffta.h"

void func_08005318(void *table, void *object, u32 index, u32 flag);

void func_080CB980(void *object, u32 value)
{
    u16 index = value;

    func_08005318((void *)0x083C83FC, object, index, 1);
}
