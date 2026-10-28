#include "ffta.h"

/* Target: [0x08003088, 0x080030D8), 80 bytes, 38 instructions. */
void func_08003088(s16 value, u8 *buffer)
{
    int remaining;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = (value & 7) + '0';
        remaining--;
    } while ((value = (value >> 3) & 0x1fff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ';
}
