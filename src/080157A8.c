#include "ffta.h"

/* Complete [0x080157A8, 0x08015858): 176 bytes, 88 instructions. */
void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                   u8 height, u8 stride, u16 tile, u8 palette)
{
    u16 offset = row * stride + column;
    u16 *destination = tilemap + offset;
    u16 current;
    u16 row_stride;
    u16 remaining;
    u16 index;

    current = tile + (palette << 12);
    row_stride = stride * 2;
    for (remaining = height; remaining != 0; remaining--) {
        for (index = 0; index < width; index++) {
            destination[index] = current++;
            (destination + stride)[index] = current++;
        }
        destination += row_stride;
    }
}
