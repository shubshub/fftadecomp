#include "ffta.h"

/* 08003134..08003188: 84 bytes. */
void func_08003134(s16 value, u8 *destination)
{
    u32 remaining;

    destination += 6;
    *destination-- = 0;
    remaining = 6;
    do {
        s16 digit = value & 0xF;

        *destination-- = digit <= 9 ? digit + 0x30 : digit + 0x37;
        remaining--;
        value = (u16)value >> 4;
    } while ((u16)value != 0);
    while (remaining-- != 0)
        *destination-- = 0x20;
}
