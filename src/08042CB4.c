#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
} TileMap08042CB4;

/* 0x08042CB4..0x08042D4A: 150 bytes, 75 instructions. */
void func_08042CB4(TileMap08042CB4 *map)
{
    u16 *destination = map->tiles;
    u16 tile = (map->palette << 12) + map->first_tile;
    s32 width = map->width;
    s32 rows = map->rows;

    while (rows != 0) {
        s32 column;

        destination[0] = tile++;
        destination[1] = tile++;
        destination[width] = tile++;
        destination[width + 1] = tile++;
        for (column = 2; column <= 12; column++) {
            u16 *entry = destination + column;

            entry[0] = tile++;
            entry[width] = tile++;
        }
        destination += width * 2;
        rows--;
    }
}
