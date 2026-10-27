#include "ffta.h"

/* Complete [0x08127380, 0x08127458): 216 bytes, 104 instructions. */
typedef struct {
    s32 x : 16;
    s32 y : 16;
    s32 z : 16;
} PackedPosition;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionedObject;

typedef struct {
    u32 unknown_00;
    PositionedObject *object;
    u8 unknown_08[7];
    u8 mode;
    u16 unknown_10;
    u16 cell_x;
    u16 cell_y;
    u16 cell_z;
} MovementState;

static inline s32 planar_distance(const PackedPosition *first, const PackedPosition *second)
{
    s32 dx = first->x - second->x;
    s32 dz;

    if (dx < 0)
        dx = -dx;
    dz = first->z - second->z;
    if (dz < 0)
        dz = -dz;
    return dx >= dz ? dx : dz;
}

static inline u32 in_distance_band(s32 distance, s32 minimum, s32 limit)
{
    if (distance < minimum)
        return 0;
    return distance < limit;
}

u32 func_08127380(MovementState *state)
{
    PackedPosition current;
    PackedPosition target;
    s32 distance;

    current.x = state->object->x;
    current.y = state->object->y;
    current.z = state->object->z;
    target.x = state->cell_x * 32 + 16;
    target.z = state->cell_z * 32 + 16;
    target.y = state->cell_y * 32 + 16;

    distance = planar_distance(&current, &target);

    if (distance >= 8 && (distance < 16 ||
        in_distance_band(distance, 16, 24))) {
        if (state->mode == 1)
            return 2;
        if (state->mode == 3)
            return 0;
    } else {
        if (state->mode == 0)
            return 1;
        if (state->mode == 2)
            return 3;
    }
    return state->mode;
}
