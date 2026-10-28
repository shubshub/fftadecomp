#include "ffta.h"

struct State0805871C {
    u8 unknown_00[0x1A];
    u8 base;
};

/* Complete [0x0805871C, 0x0805872C): 16 bytes, 8 instructions. */
u8 func_0805871C(struct State0805871C *state, u8 value)
{
    return value + state->base;
}
