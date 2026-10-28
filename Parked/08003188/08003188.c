#include "ffta.h"

/* 08003188..080031E8: 96 bytes. */
void func_08003188(s16 value, u16 *destination, u16 attributes)
{
    u32 remaining = 6;

    destination += 6;
    *destination-- = 0;
    do {
        *destination-- = ((value & 0xF) > 9
                           ? (value & 0xF) + 0x37
                           : (value & 0xF) + 0x30) | attributes;
        remaining--;
        value = (u16)value >> 4;
    } while (value != 0);
    while (remaining-- != 0)
        *destination-- = 0x20 | attributes;
}
