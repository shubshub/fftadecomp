#include "ffta.h"

struct State080A8940 {
    u8 unknown00[0x3C];
    void *allocation;
};

extern void func_08022854(void *allocation);

/* Complete [0x080A8940, 0x080A8956): 22 bytes, 9 instructions. */
void func_080A8940(struct State080A8940 *state)
{
    func_08022854(state->allocation);
    func_08022854(state);
}
