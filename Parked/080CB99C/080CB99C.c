// func_080CB99C - 0x080CB99C
//
// target bytes (ROM 0x080CB99C..0x080CB9AF):
//   00 04 03 49 c0 0b 04 30 40 18 00 78 00 09 70 47 e4 7f 3c 08
//
// 16 bytes of code plus a 4-byte literal pool at 0x080CB9AC.

#include "ffta.h"

u8 func_080CB99C(u32 value)
{
    u16 index = value;

    return ((u8 *)0x083C7FE4)[index * 2 + 4] >> 4;
}
