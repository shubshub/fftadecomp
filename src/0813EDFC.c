#include "ffta.h"

/* Complete [0x0813EDFC, 0x0813EE16): 26 bytes, 13 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 count;
    u8 unknown_0a[0x64];
    u16 current;
} SequenceState;

u32 func_0813EDFC(const SequenceState *state)
{
    if (state->current >= state->count - 1)
        return 1;
    return 0;
}
