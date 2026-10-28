#include "ffta.h"

/* 080031E8..0800323A: 82 bytes, 41 instructions. */
void func_080031E8(u16 value, u8 *buffer, s32 width)
{
    u8 *cursor = buffer + width;

    *cursor-- = 0;
    do {
        s32 digit = value % 16;

        *cursor-- = digit <= 9 ? digit + '0' : digit + 'A' - 10;
        width--;
    } while ((value >>= 4) != 0);

    while (--width != -1)
        *cursor-- = ' ';
}
