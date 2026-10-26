#include "ffta.h"

/* Target: complete [0x08127C94, 0x08127D0C), 120 bytes. */
typedef signed long long s64;

typedef struct {
    u8 unknown_00[0x0a];
    u16 frame;
} Output08127C94;

typedef struct {
    u32 unknown_00;
    Output08127C94 *output;
    u8 unknown_08[0x40];
    s64 step;
    s64 position;
    s64 limit;
    u8 unknown_60[0x60];
    u16 frames[0];
} State08127C94;

extern s64 func_08142280(s64 numerator, s64 denominator);

u32 func_08127C94(State08127C94 *state)
{
    Output08127C94 *output;

    state->position += state->step;
    if (state->position > state->limit)
        state->position = state->limit;
    output = state->output;
    output->frame = state->frames[(u32)(
        func_08142280(state->position << 16, state->step) >> 16)];
    return state->position == state->limit;
}
