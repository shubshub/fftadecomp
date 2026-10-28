#include "ffta.h"

struct State080111A8 {
    u8 unknown_00[0x14];
    u16 flags;
};

/* Target: [0x080111A8, 0x080111CC), 36 bytes, 15 instructions. */
void func_080111A8(struct State080111A8 *state, u8 enabled)
{
    if (enabled)
        state->flags |= 8;
    else
        state->flags &= ~8;
}
