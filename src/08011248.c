#include "ffta.h"

struct State08011248 {
    u8 unknown_00[0x14];
    u16 flags;
};

/* 0x08011248..0x08011280 - 56 bytes: select one of two state flags. */
void func_08011248(struct State08011248 *state, u8 enabled)
{
    if (enabled) {
        state->flags |= 0x400;
        state->flags &= ~0x800;
    } else {
        state->flags &= ~0x400;
        state->flags |= 0x800;
    }
}
