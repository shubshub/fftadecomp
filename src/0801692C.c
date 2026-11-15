#include "ffta.h"

/* 0x0801692C .. 0x08016A08: 220 bytes.
 * Write the corner tile to the four corners of the rectangle (flip bits
 * 0, 0x400, 0x800, 0xC00) and the fill tile to every other cell. */
void func_0801692C(void *destination, u8 width, u8 height, u16 flags,
                   u8 stride, u16 corner_tile, u16 fill_tile, u8 palette)
{
    u16 *buffer;
    u16 tile;
    u16 right;
    u16 bottom_offset;
    s32 row;
    s32 x;

    if (width < 2 || height < 2)
        return;

    buffer = destination;
    tile = corner_tile + (palette << 12);
    right = width - 1;
    bottom_offset = (height - 1) * stride;
    buffer[0] = tile;
    buffer[right] = tile + 0x400;
    buffer[bottom_offset] = tile + 0x800;
    (buffer + right)[bottom_offset] = tile + 0xC00;

    tile = fill_tile + (palette << 12);
    for (x = 1; x < width - 1; x++) {
        buffer[x] = tile;
        buffer[bottom_offset + x] = tile;
    }

    buffer += stride;
    for (row = height - 2; row != 0; row--) {
        for (x = 0; x < width; x++)
            buffer[x] = tile;
        buffer += stride;
    }
}
