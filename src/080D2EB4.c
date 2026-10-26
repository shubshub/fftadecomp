#include "ffta.h"

struct State080D2EB4 {
    u8 unknown_00[2];
    u8 unknown_02_low : 6;
    u8 flag_02 : 1;
    u8 unknown_02_high : 1;
    u8 unknown_03 : 7;
    u8 flag_03 : 1;
    u8 unknown_04;
    u8 unknown_05 : 1;
    u8 value_05 : 7;
};

/* Complete [0x080D2EB4, 0x080D2EE8): 52 bytes, 26 instructions. */
void func_080D2EB4(struct State080D2EB4 *state, u16 enabled)
{
    state->flag_02 = 1;
    state->flag_03 = 1;
    if (enabled)
        state->value_05 = 100;
    else
        state->value_05 = 0;
}
