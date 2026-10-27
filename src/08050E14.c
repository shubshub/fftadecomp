#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 flags;
} FlagState;

/* 08050E14..08050E1C: 8 bytes, 4 instructions. */
u32 func_08050E14(const FlagState *state)
{
    return state->flags & 1;
}
