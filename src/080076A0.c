#include "ffta.h"

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

/* Target: complete [0x080076A0, 0x080076F4), 84 bytes, 42 instructions. */
void func_080076A0(LineState *state)
{
    if (state->remaining > 0) {
        state->remaining--;
        state->y += state->stepY;
        state->accumulator += state->deltaX;
        while (state->accumulator >= state->deltaY) {
            state->x += state->stepX;
            state->accumulator -= state->deltaY;
        }
        if (state->error > 0 && state->accumulator >= state->error) {
            state->accumulator -= state->deltaY;
            state->x += state->stepX;
        }
    }
}
