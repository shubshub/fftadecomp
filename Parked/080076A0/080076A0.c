#include "ffta.h"

typedef struct {
    s32 x;
    s32 y;
    s32 unknown_08;
    s32 unknown_0c;
    s32 x_step;
    s32 y_step;
    s32 remainder_step;
    s32 period;
    s32 remainder;
    s32 threshold;
    s32 ticks;
} MotionState080076A0;

/* 0x080076A0 - 84 bytes. */
void func_080076A0(MotionState080076A0 *state)
{
    if (state->ticks > 0) {
        s32 threshold;
        s32 period;

        state->ticks--;
        state->y += state->y_step;
        state->remainder += state->remainder_step;
        period = state->period;
        threshold = state->threshold;
        if (state->remainder >= period) {
            do {
                state->x += state->x_step;
                state->remainder -= period;
            } while (state->remainder >= period);
        }
        if (threshold > 0 && state->remainder >= threshold) {
            state->remainder -= state->period;
            state->x += state->x_step;
        }
    }
}
