#include "ffta.h"

struct State080DD720 {
    u8 unknown_00[0x30];
    u32 flags;
};

/* Complete [0x080DD720, 0x080DD728): 8 bytes, 4 instructions. */
void func_080DD720(struct State080DD720 *state, u32 mask)
{
    state->flags |= mask;
}
