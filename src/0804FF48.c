#include "ffta.h"

/* 0x0804FF48..0x0804FFB6: 110 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16[8];
    u8 mode;
} TileMap;

extern u16 func_080161A0(u8 x, u8 y, u8 mode);

void func_0804FF48(TileMap *map, u16 x, u16 y)
{
    u16 *tiles = map->tiles + func_080161A0(x, y, map->mode);

    tiles[0] = tiles[1] = 0;
    tiles += map->stride;
    tiles[0] = tiles[1] = 0;

    tiles = map->tiles + func_080161A0(x - 1, y + 2, map->mode);
    tiles[0] = tiles[1] = tiles[2] = 0;
}
