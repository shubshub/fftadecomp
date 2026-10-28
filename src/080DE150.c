#include "ffta.h"

struct State080DE150 {
    u8 unknown_00[0x1F];
    s8 value;
};

extern void func_0809836C(struct State080DE150 *state, u16 first,
                          s32 value, u16 second);

/* Complete [0x080DE150, 0x080DE168): 24 bytes, 11 instructions. */
void func_080DE150(struct State080DE150 *state, u16 first, u16 second)
{
    func_0809836C(state, first, state->value, second);
}
