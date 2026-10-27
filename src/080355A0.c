#include "ffta.h"

/* 080355A0..080355E2: 66 bytes, 33 instructions. */
void func_080355A0(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = *source++;
        destination += stride;
    }
}
