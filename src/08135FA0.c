#include "ffta.h"

/* 0x08135FA0..0x08135FFC: 92 bytes. */
void func_08135FA0(const u16 *source, u16 *destination, u16 count,
                   u8 width, u16 offset)
{
    u16 index = 0;
    u16 column = 0;
    u16 row = 0;

    for (; index < count; index++, column++) {
        if (width <= column) {
            row += 32;
            column = 0;
        }
        destination[row + column] = source[index] + offset;
    }
}
