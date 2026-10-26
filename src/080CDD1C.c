#include "ffta.h"

/* 0x080CDD1C..0x080CDD3E: 34 bytes. */
typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} State;

void func_080CDD1C(State *state, u8 enabled)
{
    u8 mask = 2;

    state->flags &= ~mask;
    if (enabled)
        state->flags |= mask;
}
