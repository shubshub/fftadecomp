#include "ffta.h"

struct State080BDCD0 {
    u8 unknown00[0x400];
    u8 flags[0x100];
};

/* Complete [0x080BDCD0, 0x080BDD08): 56 bytes, 28 instructions. */
s32 func_080BDCD0(const struct State080BDCD0 *state, u8 column,
                  u8 row, u8 direction)
{
    if (direction > 3)
        return 1;
    if ((state->flags[column + row * 16] >> direction) & 1)
        return 0;
    return 1;
}
