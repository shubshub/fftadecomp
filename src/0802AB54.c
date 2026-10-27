#include "ffta.h"

/* 0x0802AB54..0x0802AB5A: 6 bytes / 3 instructions. */
struct State0802AB54 {
    u8 unknown_00[0x80];
    u8 value;
};

u8 func_0802AB54(const struct State0802AB54 *state)
{
    return state->value;
}
