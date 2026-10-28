#include "ffta.h"

struct State080DE268 {
    u8 unknown_00[0x1F];
    s8 value;
};

extern void func_080DE278(struct State080DE268 *state, s32 value);

/* Complete [0x080DE268, 0x080DE276): 14 bytes, 6 instructions. */
void func_080DE268(struct State080DE268 *state)
{
    func_080DE278(state, state->value);
}
