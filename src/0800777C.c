#include "ffta.h"

typedef struct {
    s32 position;
    s32 secondary_position;
    s32 unknown_08[2];
    s32 position_step;
    s32 secondary_step;
    s32 phase_step;
    s32 period;
    s32 phase;
    s32 threshold;
    s32 remaining;
} State0800777C;

/* 0x0800777C - 104 bytes. */
void func_0800777C(State0800777C *state, u16 count)
{
    if (state->remaining > 0) {
        if (count > state->remaining)
            count = state->remaining;

        state->remaining -= count;
        state->secondary_position += state->secondary_step * count;
        state->phase += state->phase_step * count;
        while (state->phase >= state->period) {
            state->position += state->position_step;
            state->phase -= state->period;
        }

        if (state->threshold > 0 && state->phase >= state->threshold) {
            state->phase -= state->period;
            state->position += state->position_step;
        }
    }
}
