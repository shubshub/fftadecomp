// func_080CB9B0 - 0x080CB9B0, 28 bytes (0x16 code + 2 pad + 4 literal pool)
//
// target bytes (ROM 0x080CB9B0..0x080CB9CB):
//   00 b5 03 1c 0a 06 12 0e 03 48 19 1c 01 23 39 f7 ab fc
//   01 bc 00 47 00 00 64 3d 3d 08
//
// The indexed span (16 bytes, ending at 0x080CB9C0) stops before the literal
// pool; the body runs to the interworking return at 0x080CB9C4 and the pool
// word is at 0x080CB9C8, so the function is 28 bytes.
//
// What it does: it hands the object and an index to the shared helper
// func_08005318, with the read-only table at 0x083D3D64 and a fixed fourth
// argument of 1.
//
// Build notes:
//  - The index parameter is taken wide and narrowed in a local, so the mask
//    lands inside this function: `lsls #24 / lsrs #24` is the u8 narrowing of
//    the incoming value.
//  - The table address is a plain literal, so it reaches the call as one
//    pool entry (0x083D3D64) next to the code.

#include "ffta.h"

void func_08005318(void *table, void *object, u32 index, u32 flag);

void func_080CB9B0(void *object, u32 value)
{
    u8 index = value;

    func_08005318((void *)0x083D3D64, object, index, 1);
}
