#include "ffta.h"

/* 0x080BB370..0x080BB424: 180 bytes. */
typedef struct {
    s32 x;
    s32 y;
    s32 target_x;
    s32 target_y;
    u32 unknown_10;
    s32 counter;
    s32 step;
} Transition;

typedef struct {
    u8 unknown_00[8];
    u8 active;
    s8 timer;
    u8 unknown_0A[2];
    Transition first;
    Transition second;
} State;

static inline void update_step(Transition *transition)
{
    s32 delta_x = transition->target_x - transition->x;
    s32 delta_y;
    s32 step;

    if (delta_x < 0)
        delta_x = -delta_x;
    delta_y = transition->target_y - transition->y;
    if (delta_y < 0)
        delta_y = -delta_y;
    if (delta_x >= delta_y)
        delta_y = delta_x;
    step = delta_y / 16;
    if (step <= 256)
        step = 256;
    transition->step = step;
}

void func_080BB370(State *state)
{
    update_step(&state->first);
    update_step(&state->second);

    if (state->first.step <= 256 && state->second.step <= 256)
        state->active = 0;

    ++state->timer;
    if (state->timer > 3) {
        state->timer = 0;
        ++state->first.counter;
        if (state->first.counter > 100)
            state->first.counter = 100;
        ++state->second.counter;
        if (state->second.counter > 100)
            state->second.counter = 100;
    }
}
