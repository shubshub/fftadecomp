#include "ffta.h"

void func_080897C4(u16 *destination, u16 value, u16 stride,
                   u16 width, u16 height, u16 attributes, s32 step)
{
    s32 row_stride = stride - 2;
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            destination[column] = value | attributes;
            value += step;
        }
        destination += row_stride;
    }
}
