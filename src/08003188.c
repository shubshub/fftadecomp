#include "ffta.h"

/* Target: [0x08003188, 0x080031E8), 96 bytes, 48 instructions. */
void func_08003188(s16 value, u16 *buffer, u16 attributes)
{
    int remaining;
    int digit;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = ((digit = value & 0xf) < 10 ? digit + '0'
                                                : digit + 'A' - 10) | attributes;
        remaining--;
    } while ((value = (value >> 4) & 0xfff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ' | attributes;
}
