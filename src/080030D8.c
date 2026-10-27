#include "ffta.h"

/* Target: [0x080030D8, 0x08003134), 92 bytes, 44 instructions. */
void func_080030D8(s16 value, u16 *buffer, u16 attributes)
{
    int remaining;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = ((value & 7) + '0') | attributes;
        remaining--;
    } while ((value = (value >> 3) & 0x1fff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ' | attributes;
}
