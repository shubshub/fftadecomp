#include "ffta.h"

/* 0x080A9588..0x080A95AE: 38 bytes, 16 instructions, including literal pool. */
typedef struct {
    u32 unknown_00;
    u32 position;
    u32 target_position;
    u32 previous_position;
    u8 flags;
} MovementPositionState;

extern MovementPositionState data_0200FFC8;

u32 func_080A9588(void)
{
    MovementPositionState *state = &data_0200FFC8;

    if (state->flags & 1) {
        if (state->target_position != state->position) {
            return 0;
        }
    }
    return 1;
}
