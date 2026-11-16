#include "ffta.h"

/* Target: [0x080031E8, 0x0800323A), 82 bytes, 41 instructions. */
void func_080031E8(s16 value, u8 *buffer, int width)
{
    int digit;

    buffer += width;
    *buffer-- = 0;
    do {
        *buffer-- = (digit = value & 0xf) < 10 ? digit + '0'
                                               : digit + 'A' - 10;
        width--;
    } while ((value = (value >> 4) & 0xfff) != 0);

    while (width-- != 0)
        *buffer-- = ' ';
}
