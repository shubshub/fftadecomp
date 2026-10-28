#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid;

/* Complete target: [0x0802B4A8, 0x0802B53C), 148 bytes. */
void func_0802B4A8(TileGrid *grid, u8 x, u8 y, const u16 *source, u8 width, u8 height)
{
    u16 *tiles = grid->tiles;
    u8 row;
    u8 column;

    for (row = 0; row < height; row++) {
        u16 row_offset = grid->width * (row + (s8)y);
        u32 source_offset = width * row;
        for (column = 0; column < width; column++) {
            if ((u32)((s8)x + column) <= 30) {
                tiles[row_offset + column + (s8)x] = source[source_offset + column];
            }
        }
    }
}
