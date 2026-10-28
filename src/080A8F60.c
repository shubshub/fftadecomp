#include "ffta.h"

typedef struct {
    u8 index;
    s8 selection;
    s8 previous_selection;
    u8 unknown_03;
    s16 x;
    s16 y;
    s16 target_x;
    s16 target_y;
    s16 previous_x;
    s16 previous_y;
    u8 flags;
} State080A8F60;

/* 0x080A8F60 .. 0x080A8FBC: 92 bytes, including literal pool. */
void func_080A8F60(State080A8F60 *state)
{
    s32 initialized;

    state->index = 0xFF;
    state->selection = -1;
    state->previous_selection = -1;
    initialized = state->flags & 1;
    if (!initialized || state->y > 127) {
        state->target_x = 192;
        state->target_y = 128;
        if (initialized) {
            state->flags = 1;
        } else {
            state->flags = 1;
            state->x = 192;
            state->y = 160;
        }
    } else {
        state->previous_x = state->target_x;
        state->previous_y = state->target_y;
        state->target_x = 192;
        state->target_y = -32;
        state->flags = 7;
    }
}
