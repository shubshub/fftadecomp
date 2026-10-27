#include "ffta.h"

typedef struct TilePosition0801CAB8 {
    s8 x;
    s8 y;
} TilePosition0801CAB8;

typedef struct WorldPosition0801CAB8 {
    s16 x;
    s16 y;
} WorldPosition0801CAB8;

static inline void tile_to_world(s16 x, s16 height, s16 y,
                          s16 *world_x, s16 *world_height, s16 *world_y)
{
    *world_x = x * 32 + 16;
    *world_height = height * 16;
    *world_y = y * 32 + 16;
}

/* Complete [0x0801CAB8, 0x0801CAE0): 40 bytes, 20 instructions. */
void func_0801CAB8(const TilePosition0801CAB8 *tile,
                   WorldPosition0801CAB8 *world)
{
    s16 height;

    tile_to_world(tile->x, 0, tile->y, &world->x, &height, &world->y);
}
