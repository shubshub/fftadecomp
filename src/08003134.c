#include "ffta.h"

/* Target: [0x08003134, 0x08003188), 84 bytes, 42 instructions. */
void func_08003134(s16 value, u8 *buffer)
{
    int remaining;
    int digit;

    buffer += 6;
    *buffer-- = 0;
    remaining = 6;
    do {
        *buffer-- = (digit = value & 0xf) < 10 ? digit + '0'
                                               : digit + 'A' - 10;
        remaining--;
    } while ((value = (value >> 4) & 0xfff) != 0);

    while (remaining-- != 0)
        *buffer-- = ' ';
}
