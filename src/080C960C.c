#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F70];
    u8 flags[0];
} FlagState;

void func_080C960C(u16 index, u16 value, FlagState *state)
{
    u8 *flag = &state->flags[index >> 3];
    u8 mask = 1 << (index & 7);

    *flag &= ~mask;
    if (value)
        *flag |= mask;
}
