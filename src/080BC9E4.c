#include "ffta.h"

struct State080BC9E4 {
    u8 unknown00[0x172];
    u8 flag;
};

/* Complete [0x080BC9E4, 0x080BC9F0): 12 bytes, 6 instructions. */
void func_080BC9E4(struct State080BC9E4 *state)
{
    state->flag = 1;
}
