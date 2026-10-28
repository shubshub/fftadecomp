#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_06[2];
} Position;

typedef struct {
    u8 unknown_00[0x14];
} Projection;

typedef struct {
    Projection vertical;
    Projection planar;
    s16 difference_x;
    s16 difference_y;
    s16 difference_z;
    s16 distance;
    Position start;
    Position end;
} PathState;

void func_080A7FC4(Projection *projection, s16 start_x, s16 start_y,
                   s16 end_x, s16 end_y);

void func_080A04E8(PathState *state, const Position *start,
                   const Position *end)
{
    s32 difference;

    difference = end->x - start->x;
    if (difference < 0)
        difference = -difference;
    state->difference_x = difference;
    difference = end->y - start->y;
    if (difference < 0)
        difference = -difference;
    state->difference_y = difference;
    difference = end->z - start->z;
    if (difference < 0)
        difference = -difference;
    state->difference_z = difference;

    state->start.x = start->x;
    state->start.y = start->y;
    state->start.z = start->z;
    state->end.x = end->x;
    state->end.y = end->y;
    state->end.z = end->z;
    func_080A7FC4(&state->planar, start->x, start->z, end->x, end->z);

    difference = end->y - start->y;
    if (difference < 0)
        difference = -difference;
    state->difference_y = difference;
    if (state->difference_x >= state->difference_z) {
        func_080A7FC4(&state->vertical, start->x, start->y, end->x, end->y);
        state->distance = state->difference_x;
    } else {
        func_080A7FC4(&state->vertical, start->z, start->y, end->z, end->y);
        state->distance = state->difference_z;
    }
}
