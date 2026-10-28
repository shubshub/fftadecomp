#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
} State;

extern State g_state_02007F40;

/* Complete [0x0801D918, 0x0801D928): 16 bytes, 6 instructions. */
void func_0801D918(void)
{
    State *state = &g_state_02007F40;

    state->flags |= 2;
}
