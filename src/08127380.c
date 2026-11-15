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
    u8 unknown_00[4];
    MovingEntity *entity;
    u8 unknown_08[7];
    u8 facing;
    u8 unknown_10[2];
    u16 tile_x;
    u16 tile_height;
    u16 tile_y;
} MovementState;

/* Complete [0x08127380, 0x08127458): 216 bytes, 104 instructions. */
u32 func_08127380(MovementState *state)
{
    Position current;
    Position target;
    const Position *first;
    const Position *second;
    s32 delta_x;
    s32 delta_y;
    s32 distance;
    u32 middle_band;

    current.x = state->entity->x;
    current.height = state->entity->height;
    current.y = state->entity->y;
    target.x = state->tile_x * 32 + 16;
    target.y = state->tile_y * 32 + 16;
    target.height = state->tile_height * 32 + 16;

    /* Both records are addressed only after their members are written: the
     * ROM inserts the members a word at a time, then reads them back as
     * halfwords through pointers. */
    first = &current;
    second = &target;
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
        if (state->facing == 1)
            return 2;
        if (state->facing == 3)
            return 0;
        return state->facing;
    } else {
        if (state->facing == 0)
            return 1;
        if (state->facing == 2)
            return 3;
        return state->facing;
    }
}
