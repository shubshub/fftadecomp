#include "ffta.h"

void func_0801692C(u16 *destination, u8 width, u8 height, u32 unused,
                   u8 stride, u16 corner_tile, u16 fill_tile, u8 palette)
{
    u16 *top;
    u16 *bottom;
    u16 *right_corner;
    u16 right;
    u16 bottom_offset;
    u16 tile;
    s32 x;
    u32 rows = height;

    if (width <= 1 || rows <= 1)
        return;
    top = destination;
    tile = corner_tile + (palette << 12);
    right = width - 1;
    bottom_offset = (rows - 1) * stride;
    top[0] = tile;
    right_corner = top + right;
    right_corner[0] = tile + 0x400;
    bottom = top + bottom_offset;
    bottom[0] = tile + 0x800;
    right_corner[bottom_offset] = tile + 0xC00;
    tile = fill_tile + (palette << 12);
    rows -= 2;
    for (x = 1; x < width - 1; x++) {
        top[x] = tile;
        bottom[x] = tile;
    }
    top += stride;
    while (rows) {
        rows--;
        for (x = 0; x < width; x++)
            top[x] = tile;
        top += stride;
    }
}
