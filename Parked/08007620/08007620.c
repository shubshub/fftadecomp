#include "ffta.h"

typedef struct TransitionState {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 step_first;
    u16 step_second;
    s16 delta_first;
    s16 delta_second;
    s16 error;
    s16 half_second;
    s16 remaining;
} TransitionState;

void func_08007620(void *object, u16 first, u16 second,
                   u16 target_first, u16 target_second)
{
    TransitionState *state = object;
    s32 difference;

    state->first = first;
    state->second = second;
    state->target_first = target_first;
    state->target_second = target_second;
    difference = (s16)target_first - (s16)first;
    state->delta_first = difference;
    if (state->delta_first < 0) {
        state->delta_first = -difference;
        state->step_first = 0xFFFF;
    } else {
        state->step_first = 1;
    }
    difference = (s16)target_second - (s16)second;
    state->delta_second = difference;
    if (state->delta_second < 0) {
        state->delta_second = -difference;
        state->step_second = 0xFFFF;
    } else {
        state->step_second = 1;
    }
    state->half_second = state->delta_second >> 1;
    state->error = 0;
    state->remaining = state->delta_second;
    if (state->delta_second == 0) {
        state->first = target_first;
    }
}
