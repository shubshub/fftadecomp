#include "ffta.h"

/* Target: complete [0x0801CA10, 0x0801CA46), 54 bytes. */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
} WorldPoint0801CA10;

typedef struct {
    u8 x;
    u8 y;
    u8 z;
} GridPoint0801CA10;

static inline void world_to_grid(s16 x, s16 y, s16 z,
                                 s16 *grid_x, s16 *grid_y, s16 *grid_z)
{
    *grid_x = x >> 5;
    *grid_y = y >> 4;
    *grid_z = z >> 5;
}

void func_0801CA10(const WorldPoint0801CA10 *world, GridPoint0801CA10 *point)
{
    s16 grid_x;
    s16 grid_y;
    s16 grid_z;

    world_to_grid(world->x, world->y, world->z, &grid_x, &grid_y, &grid_z);
    point->x = grid_x;
    point->y = grid_y;
    point->z = grid_z;
}
