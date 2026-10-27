#include "ffta.h"

/* 0x08035638..0x08035678: 64 bytes / 32 instructions. */
void func_08035638(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride, u16 value)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = value;
        destination += stride;
    }
}
