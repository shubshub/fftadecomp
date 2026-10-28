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

/* Target: complete [0x080075CC, 0x0800761E), 82 bytes. */
void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY)
{
    state->x = x;
    state->y = y;
    state->endX = endX;
    state->endY = endY;

    state->deltaX = endX - x;
    if (state->deltaX < 0)
    {
        state->deltaX = -state->deltaX;
        state->stepX = -1;
    }
    else
        state->stepX = 1;

    state->deltaY = endY - y;
    if (state->deltaY < 0)
    {
        state->deltaY = -state->deltaY;
        state->stepY = -1;
    }
    else
        state->stepY = 1;

    state->error = state->deltaY >> 1;
    state->accumulator = 0;
    state->remaining = state->deltaY;
    if (state->deltaY == 0)
        state->x = endX;
}
