#include "ffta.h"

typedef struct {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 first_step;
    u16 second_step;
    u16 first_delta;
    u16 second_delta;
    u16 error;
    u16 half_delta;
    u16 remaining;
} LineStepState;

void func_080076F4(void *object)
{
    LineStepState *state = object;

    if ((s16)state->remaining > 0) {
        u16 error;
        u16 delta;
        u16 half_delta;

        state->remaining--;
        state->second += state->second_step;
        error = state->first_delta + state->error;
        state->error = error;
        delta = state->second_delta;
        half_delta = state->half_delta;
        if ((s16)error >= (s16)delta) {
            u16 step = state->first_step;
            u16 first = state->first;

            do {
                first += step;
                error -= delta;
            } while ((s16)error >= (s16)delta);
            state->error = error;
            state->first = first;
        }
        if ((s16)half_delta > 0 && (s16)state->error >= (s16)half_delta) {
            state->error -= delta;
            state->first += state->first_step;
        }
    }
}
