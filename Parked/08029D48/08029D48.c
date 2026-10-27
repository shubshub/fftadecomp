#include "ffta.h"

typedef struct TileMap {
    u8 unknown_00[0x14];
    u16 *map;
} TileMap;

extern TileMap data_030008B0;
extern void func_08029688(TileMap *state, u8 x, u8 y, u8 digits,
                          u32 value, u8 palette);

/* 08029D48..08029DD2: 138 bytes, 66 instructions. */
void func_08029D48(u8 x, u8 y, u8 value, u8 palette)
{
    TileMap *state = &data_030008B0;
    u16 *map = state->map;
    u32 cell = y * 32 + x;
    u16 *tiles = &map[cell];

    tiles[0xa1] = 0x73 | (palette << 12);
    tiles[0xa2] = 0x74 | (palette << 12);
    if (value != 0) {
        func_08029688(state, x + 2, y + 5, 2, value, palette);
    } else {
        tiles[0xa3] = 0x75 | (palette << 12);
        tiles[0xa4] = 0x75 | (palette << 12);
    }
}
