#include "ffta.h"

struct Tilemap0802B2E8 {
    u8 unknown_00[0x0c];
    u8 stride;
    u8 unknown_0d[7];
    u16 *tiles;
};

/* Target: [0x0802B2E8, 0x0802B366), 126 bytes, 63 instructions. */
void func_0802B2E8(struct Tilemap0802B2E8 *tilemap,
                   u8 x, u8 y, u8 width, u8 height)
{
    u16 row;
    u16 column;
    u16 row_offset;

    for (row = 0; row < height; row++) {
        row_offset = tilemap->stride * (row + y);
        for (column = 0; column < width; column++)
            tilemap->tiles[row_offset + x + column] = 0;
    }
}
