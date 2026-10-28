#include "ffta.h"

typedef struct {
    u8 unknown_00[0x29];
    u8 flags;
} MovementState;

u32 func_0809D614(const MovementState *state)
{
    return (state->flags >> 1) & 1;
}
