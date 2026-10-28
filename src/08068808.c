#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 flags;
} State08068808;

/* Complete [0x08068808, 0x08068810): 8 bytes, 4 instructions. */
u8 func_08068808(const State08068808 *state)
{
    return state->flags & 1;
}
