#include "ffta.h"

/* 0x080D702C..0x080D7080: 84 bytes. */
void func_080D702C(const u8 *source, u16 count, u8 *destination,
                   u8 foreground, u8 palette)
{
    u16 i;
    u16 bit;
    u8 value;

    palette <<= 4;
    for (i = 0; i < count; i++) {
        value = source[i];
        for (bit = 0; bit < 8; bit++) {
            if (value & 1)
                *destination = palette | foreground;
            else
                *destination = 0;
            destination++;
            value >>= 1;
        }
    }
}
