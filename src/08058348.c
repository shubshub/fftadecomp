#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16[9];
    u8 palette;
} TileWindow;

/* Complete target: [0x08058348, 0x080583C8), 128 bytes. */
void func_08058348(TileWindow *window, s8 row, u8 palette, u8 column, u8 width)
{
    u16 tileRow = row;
    u16 *tiles = window->tiles + column + tileRow * window->stride;
    int y;
    int x;

    if (palette == 0xFF)
        palette = window->palette;

    for (y = 0; y < 2; y++) {
        for (x = 0; x < width; x++)
            tiles[x] = (tiles[x] & 0x0FFF) | (palette << 12);
        tiles += window->stride;
    }
}
