#include "ffta.h"

struct State08017B48 {
    u8 unknown_00[0x16];
    u8 value_16;
};

u8 func_08017B48(const struct State08017B48 *state)
{
    return state->value_16 * 2;
}
