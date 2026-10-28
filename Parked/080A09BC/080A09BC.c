#include "ffta.h"

typedef signed long long s64;

typedef struct {
    s64 progress;
    s64 initial_value;
    s64 distance;
    s64 velocity;
    s64 height_delta;
    s64 end_height_delta;
    s64 unknown_30[5];
} Trajectory;

typedef struct {
    u8 unknown_00[0x28];
    s16 start_x;
    s16 start_height;
    s16 start_z;
    u8 unknown_2E[2];
    s16 end_x;
    s16 end_height;
    s16 end_z;
    u8 unknown_36[0xA];
    s16 heights[2];
    s16 initial_value;
    u8 unknown_46[2];
    s16 count;
    u8 unknown_4A[6];
    s32 velocity_x[2];
    s32 velocity_z[2];
    u8 unknown_60[0x18];
    Trajectory trajectories[2];
} TrajectoryState;

u16 func_08141860(s16 horizontal, s16 vertical);
s16 func_08007A60(u8 angle);
s32 func_08007A4C(u8 angle);

void func_080A09BC(TrajectoryState *state, s32 speed)
{
    s32 difference_z = state->end_z - state->start_z;
    s32 difference_x = state->end_x - state->start_x;
    s32 absolute_x = difference_x;
    s32 absolute_z;
    s32 distance;
    u8 angle;
    s32 index;

    if (absolute_x < 0)
        absolute_x = -absolute_x;
    absolute_z = difference_z;
    if (absolute_z < 0)
        absolute_z = -absolute_z;
    distance = absolute_z;
    if (absolute_x >= absolute_z)
        distance = absolute_x;
    angle = func_08141860((s16)difference_x, (s16)difference_z) >> 8;

    for (index = 0; index < state->count; index++) {
        s32 maximum = state->heights[index];
        s32 minimum = state->heights[index];
        s32 height_delta;

        if (maximum < state->end_height)
            maximum = state->end_height;
        if (minimum > state->end_height)
            minimum = state->end_height;
        if (maximum < state->start_height)
            maximum = state->start_height;
        if (minimum > state->start_height)
            minimum = state->start_height;
        height_delta = state->heights[index] - state->start_height;

        if (maximum - minimum > distance) {
            u8 height_angle = func_08141860(
                (s16)(absolute_x >= absolute_z ? absolute_x : absolute_z),
                (s16)height_delta) >> 8;

            speed = (func_08007A60(height_angle) * speed) >> 8;
            state->velocity_x[index] = (func_08007A60(angle) * speed) >> 8;
            state->velocity_z[index] = ((s16)func_08007A4C(angle) * speed) >> 8;
        } else {
            state->velocity_x[index] = (func_08007A60(angle) * speed) >> 8;
            state->velocity_z[index] = ((s16)func_08007A4C(angle) * speed) >> 8;
        }

        state->trajectories[index].progress = 0;
        state->trajectories[index].initial_value = (s64)state->initial_value << 16;
        state->trajectories[index].distance = (s64)distance << 16;
        state->trajectories[index].velocity = 0;
        state->trajectories[index].height_delta =
            (s64)(state->heights[index] - state->start_height) << 16;
        state->trajectories[index].end_height_delta =
            (s64)(state->end_height - state->start_height) << 16;
    }
}
