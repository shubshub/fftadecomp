#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Point0809B470;

typedef struct {
    u32 unknown_00;
    Point0809B470 *points;
    s16 start_x;
    s16 start_height;
    s16 start_y;
    u8 unknown_0e[2];
    s16 end_x;
    s16 end_height;
    s16 end_y;
    u8 unknown_16[2];
    s16 count;
    s16 index;
    u8 unknown_1c[0xb];
    u8 direction;
} Path0809B470;

/* Complete [0x0809B470, 0x0809B542): 210 bytes, 105 instructions. */
u32 func_0809B470(Path0809B470 *path)
{
    Point0809B470 *current;
    Point0809B470 *next;
    s32 dx;
    s32 dy;
    s32 dz;
    u8 direction;
    s32 next_x;
    s32 current_x;

    if (path->index >= path->count - 1)
        return 0;

    current = &path->points[path->index];
    next = &path->points[path->index + 1];
    dx = next->x - current->x;
    dy = next->y - current->y;
    if (dx > 0)
        direction = 3;
    else if (dx < 0)
        direction = 1;
    else if (dy > 0)
        direction = 0;
    else if (dy < 0)
        direction = 2;
    else
        direction = 0;
    path->direction = direction;

    next_x = next->x;
    current_x = current->x;
    dz = next->height - current->height;
    dy = next->y - current->y;
    path->start_x = current_x * 32 + 16;
    path->start_height = current->height * 16;
    path->start_y = current->y * 32 + 16;
    path->end_x = next->x * 32 + 16;
    path->end_height = next->height * 16;
    path->end_y = next->y * 32 + 16;

    dx = next_x - current_x;
    if ((dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy) > 1) {
        if (dz != 0)
            return 5;
        return 4;
    }
    if (dz == 1)
        return 2;
    if (dz > 1)
        return 6;
    if (dz == -1)
        return 3;
    if (dz < -1)
        return 7;
    return 1;
}
