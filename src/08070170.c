#include "ffta.h"

typedef struct {
    u8 unknown_00[0x13];
    u8 x;
    u8 y;
} TilePosition;

typedef struct {
    u8 unknown_00[0x0C];
    u8 stride;
    u8 unknown_0D[7];
    u16 *tiles;
} TileMap;

extern void func_0802ACA0(u16 *entries, u16 first, u8 palette, u16 count);

/* Complete target: [0x08070170, 0x080701BC), 76 bytes, 31 instructions. */
void func_08070170(TilePosition *position, TileMap *map, u8 row)
{
    u16 offset = (row * 2 + position->y) * map->stride + position->x;

    func_0802ACA0(map->tiles + offset, 0x149, 13, 2);
    func_0802ACA0(map->tiles + offset + map->stride, 0x14B, 13, 2);
}
