#include "ffta.h"

/* 0x08016560 .. 0x080165C4: 100 bytes.
 * Fill rows 2 .. height - 2 of a buffer of stride-tile rows: width cells
 * per row, each fill_tile + (palette << 12).  Nothing is drawn unless
 * width >= 2 and height >= 4; flags is not read. */
void func_08016560(void *destination, u8 width, u8 height, u16 flags,
                   u8 stride, u16 fill_tile, u8 palette)
{
    u16 *buffer;
    u16 tile;
    u16 rows;
    u16 columns;
    s32 row;
    s32 x;

    if (width < 2 || height < 4)
        return;

    buffer = destination;
    columns = width;
    buffer += stride * 2;
    rows = height - 3;
    tile = fill_tile + (palette << 12);
    for (row = rows; row != 0; row--) {
        for (x = 0; x < columns; x++)
            buffer[x] = tile;
        buffer += stride;
    }
}
