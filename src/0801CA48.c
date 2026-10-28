#include "ffta.h"

/* Target: complete [0x0801CA48, 0x0801CA76), 46 bytes. */
typedef struct {
    s16 x;
    s16 z;
} WorldPoint0801CA48;

typedef struct {
    u8 x;
    u8 z;
} GridPoint0801CA48;

static inline void world_to_grid(s16 x, s16 y, s16 z,
                                 s16 *grid_x, s16 *grid_y, s16 *grid_z)
{
    *grid_x = x >> 5;
    *grid_y = y >> 4;
    *grid_z = z >> 5;
}

void func_0801CA48(const WorldPoint0801CA48 *world, GridPoint0801CA48 *point)
{
    s16 grid_x;
    s16 grid_y;
    s16 grid_z;

    world_to_grid(world->x, 0, world->z, &grid_x, &grid_y, &grid_z);
    point->x = grid_x;
    point->z = grid_z;
}
