#include "ffta.h"

typedef struct {
    s16 x;
    s16 height;
    s16 y;
} Position;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
} MovingEntity;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Point0809B120;

typedef struct {
    MovingEntity *entity;
    Point0809B120 *points;
    u8 unknown_08[0x12];
    s16 index;
    u8 unknown_1C[0xC];
    u8 facing;
} Path0809B120;

/* Complete [0x0809B120, 0x0809B216): 246 bytes, 118 instructions. */
s32 func_0809B120(Path0809B120 *path)
{
    Position current;
    Position next;
    const Position *first;
    const Position *second;
    s32 delta_x;
    s32 delta_y;
    s32 distance;
    u32 middle_band;
    s32 facing;

    current.x = path->entity->x;
    current.height = path->entity->height;
    current.y = path->entity->y;
    next.x = path->points[path->index + 1].x * 32 + 16;
    next.height = path->points[path->index + 1].height * 16;
    next.y = path->points[path->index + 1].y * 32 + 16;

    /* Both records are addressed only after their members are written: the
     * ROM inserts the members a word at a time, then reads them back as
     * halfwords through pointers. */
    first = &current;
    second = &next;
    delta_x = first->x - second->x;
    if (delta_x < 0)
        delta_x = -delta_x;
    delta_y = first->y - second->y;
    if (delta_y < 0)
        delta_y = -delta_y;
    distance = delta_x >= delta_y ? delta_x : delta_y;

    /* The ROM tests every boundary: 7, 15 and 23. */
    if (distance < 8)
        middle_band = 0;
    else if (distance < 16)
        middle_band = 1;
    else if (distance < 24)
        middle_band = 1;
    else
        middle_band = 0;

    if (middle_band) {
        if (path->facing == 1)
            facing = 2;
        else if (path->facing == 3)
            facing = 0;
        else
            facing = path->facing;
    } else {
        if (path->facing == 0)
            facing = 1;
        else if (path->facing == 2)
            facing = 3;
        else
            facing = path->facing;
    }

    if (facing != path->facing) {
        path->facing = facing;
        return 1;
    }
    return 0;
}
