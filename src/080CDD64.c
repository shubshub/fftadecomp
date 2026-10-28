#include "ffta.h"

/* 0x080CDD64..0x080CDD86: 34 bytes. */
typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} State;

void func_080CDD64(State *state, u8 enabled)
{
    u8 mask = 8;

    state->flags &= ~mask;
    if (enabled)
        state->flags |= mask;
}
