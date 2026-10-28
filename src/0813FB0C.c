#include "ffta.h"

/* Target: complete [0x0813FB0C, 0x0813FB68), 92 bytes, 46 instructions. */
void func_0813FB0C(const u16 *source, u16 *destination, u16 count,
                  u8 width, u16 offset)
{
    u16 index = 0;
    u16 column = 0;
    u16 row = 0;

    while (index < count) {
        if (width <= column) {
            row += 32;
            column = 0;
        }
        destination[row + column] = source[index] + offset;
        index++;
        column++;
    }
}
