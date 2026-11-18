#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} TilePosition;

extern void func_0809D66C(s8 direction, s8 *dx, s8 *dy);
extern s32 func_080A0254(void *unit, u8 source_x, u8 source_y,
                        u8 target_x, u8 target_y, u16 action, u16 parameter,
                        u8 flags);
extern u8 func_0801CC18(u8 x, u8 y);

/* Each successive row in front of the origin is two tiles wider. */
s32 func_080B48CC(void *unit, s8 x, s8 y, s8 direction, s8 extent,
                  u16 action, u16 parameter, TilePosition *output)
{
    s8 dx;
    s8 dy;
    s8 center_x;
    s8 center_y;
    s8 tile_x;
    s8 tile_y;
    s32 count;
    s32 depth;
    s32 i;
    s32 width;

    func_0809D66C(direction, &dx, &dy);
    center_x = x;
    center_y = y;
    count = 0;
    for (depth = 0; depth < extent; depth++) {
        center_x += dx;
        center_y += dy;
        width = depth * 2 + 1;
        tile_x = center_x - dy * depth;
        tile_y = center_y - dx * depth;
        for (i = 0; i < width; i++) {
            if (func_080A0254(unit, x, y, tile_x, tile_y, action, parameter, 0)) {
                output->x = tile_x;
                output->y = tile_y;
                output->height = func_0801CC18(tile_x, tile_y);
                output++;
                count++;
            }
            tile_x += dy;
            tile_y += dx;
        }
    }
    return count;
}
