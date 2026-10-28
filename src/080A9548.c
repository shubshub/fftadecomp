#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    s16 x;
    s16 y;
    s16 target_x;
    s16 target_y;
    s16 previous_x;
    s16 previous_y;
    u8 flags;
} State080A9548;

extern State080A9548 data_0200FFC8;

/* Complete [0x080A9548, 0x080A9588): 64 bytes, 27 instructions. */
void func_080A9548(void)
{
    State080A9548 *state = &data_0200FFC8;

    if (state->flags & 1) {
        state->previous_x = state->target_x;
        state->previous_y = state->target_y;
        if (state->y <= 4) {
            state->target_x = 192;
            state->target_y = -32;
        } else {
            state->target_x = 192;
            state->target_y = 160;
        }
        state->flags = 5;
    }
}
