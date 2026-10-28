#include "ffta.h"

/* 0x08016800 .. 0x0801692A: 298 bytes. */
static inline void fill_rectangle(u16 *destination, u16 width, u16 height,
                                  u8 stride, u16 tile)
{
    s32 rows = height;

    while (rows--) {
        u16 *output = destination;
        s32 columns = width;

        while (columns--)
            *output++ = tile;
        destination += stride;
    }
}

void func_08016800(u16 *destination, u8 width, u8 height, u8 unused,
                   u8 stride, u16 border_tile, u16 fill_tile, u8 palette)
{
    u16 right;
    u16 bottom;
    u16 offset;
    s32 index;

    if (width < 2 || height < 2)
        return;

    border_tile += palette << 12;
    right = width - 1;
    bottom = stride * (height - 1);
    destination[0] = border_tile;
    destination[right] = border_tile + 1;
    destination[bottom] = border_tile + 2;
    destination[bottom + right] = border_tile + 3;

    for (index = 1; index < width - 1; index++) {
        destination[index] = border_tile + 6;
        destination[bottom + index] = border_tile + 7;
    }

    offset = 0;
    for (index = 1; index < height - 1; index++) {
        offset += stride;
        destination[offset] = border_tile + 4;
        destination[offset + right] = border_tile + 5;
    }

    fill_rectangle(destination + stride + 1, width - 2, height - 2,
                   stride, fill_tile + (palette << 12));
}
