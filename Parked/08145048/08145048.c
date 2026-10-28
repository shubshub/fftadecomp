#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x15];
    u8 unknown_16;
    u8 unknown_17;
    u8 mode;
    u8 unknown_19;
    u8 unknown_1A;
} State;

/* Complete [0x08145048, 0x08145062): 26 bytes, 13 instructions. */
void func_08145048(void *context, State *state)
{
    u32 mask;
    state->unknown_16 = 0;
    state->unknown_1A = 0;
    if (state->mode == 0)
        mask = 12;
    else
        mask = 3;
    state->flags |= mask;
}
