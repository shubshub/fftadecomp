#include "ffta.h"

/* 0x080A9E6C: 182 bytes. */
typedef struct {
    u8 unknown_00[8];
    s16 x;
    u16 unknown_0a;
    s16 z;
} Position;

typedef struct {
    Position *position;
    u8 unknown_04[0x12e];
    s8 direction_x;
    s8 direction_z;
    u8 unknown_134[2];
    s16 destination_x;
    s16 destination_z;
} MovementState;

u8 func_080A9E6C(MovementState *state, s32 distance)
{
    u8 result = 1;

    if (state->direction_x != 0) {
        state->position->x += state->direction_x * distance;
        if (state->direction_x < 0) {
            if (state->destination_x > state->position->x) {
                state->position->x = state->destination_x;
                result = 0;
            }
        } else {
            if (state->destination_x < state->position->x) {
                state->position->x = state->destination_x;
                result = 0;
            }
        }
    }
    if (state->direction_z != 0) {
        state->position->z += state->direction_z * distance;
        if (state->direction_z < 0) {
            if (state->destination_z > state->position->z) {
                state->position->z = state->destination_z;
                result = 0;
            }
        } else {
            if (state->destination_z < state->position->z) {
                state->position->z = state->destination_z;
                result = 0;
            }
        }
    }
    return result;
}
