#include "ffta.h"

/* Clear a rectangle in a tile map with a 32-entry row stride. */
void func_0813FBD4(u16 *tile_map, u8 x, u8 y, u8 width, u8 height)
{
    u16 offset = x + (y << 5);
    u8 row;
    u8 column;

    for (row = 0; row < height; row++)
    {
        for (column = 0; column < width; column++)
            tile_map[offset + column] = 0;
        offset += 32;
    }
}
