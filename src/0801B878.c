#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
} State;

extern State g_state_02007F40;

/* Complete [0x0801B878, 0x0801B888): 16 bytes, 6 instructions. */
void func_0801B878(void)
{
    State *state = &g_state_02007F40;

    state->flags |= 1;
}
