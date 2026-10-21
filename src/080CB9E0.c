// func_080CB9E0 - 0x080CB9E0, 52 bytes (0x2E code + 2 pad + 4 literal pool)
//
// target bytes (ROM 0x080CB9E0..0x080CBA13):
//   00 b5 03 1c 09 06 09 0e 4d 29 01 d0 52 29 01 d9 2d 21 02 e0
//   2b 29 00 d9 2c 21 05 48 8a 1e 12 04 12 0c 19 1c 01 23 39 f7
//   87 fc 01 bc 00 47 00 00 04 90 3b 08
//
// What it does: it maps a character-like index and hands the object and the
// mapped entry to the shared helper func_08005318, with the read-only table at
// 0x083B9004 and a fixed fourth argument of 1.
//
// Build notes:
//  - The index parameter is taken wide and narrowed in a local, so the mask
//    lands inside this function: `lsls #24 / lsrs #24` is the u8 narrowing of
//    the incoming value.
//  - The entry passed on is `index - 2` narrowed to u16, so the subtraction
//    is done first and the 16-bit mask lands after it.

#include "ffta.h"

void func_08005318(void *table, void *object, u16 index, u32 flag);

void func_080CB9E0(void *object, u32 value)
{
    u8 index = value;

    if (index == 'M' || index > 'R')
        index = '-';
    else if (index > '+')
        index = ',';

    func_08005318((void *)0x083B9004, object, index - 2, 1);
}
