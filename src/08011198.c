#include "ffta.h"

/* 0x08011198..0x080111A6: 14 bytes / 7 instructions. */
struct State08011198 {
    u8 unknown_00[0x14];
    u16 flags;
};

void func_08011198(struct State08011198 *state)
{
    state->flags |= 0x100;
}
