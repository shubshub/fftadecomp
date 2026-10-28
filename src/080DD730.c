#include "ffta.h"

struct State080DD730 {
    u8 unknown_00[0x30];
    u32 flags;
};

/* Complete [0x080DD730, 0x080DD73A): 10 bytes, 5 instructions. */
u32 func_080DD730(struct State080DD730 *state)
{
    return (state->flags >> 6) & 1;
}
