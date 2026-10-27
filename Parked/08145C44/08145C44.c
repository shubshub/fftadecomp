#include "ffta.h"

typedef struct
{
    u8 unknown_00[2];
    u8 first;
    u8 second;
    u8 unknown_04[2];
    u8 strength;
    u8 unknown_07[3];
    u8 intensity;
    u8 unknown_0B[14];
    u8 scaled;
    u8 unknown_1A;
    u8 mask;
    u8 allowed_mask;
} BalanceState;

/* Complete target: 0x08145C44..0x08145CAC, 104 bytes. */
void func_08145C44(BalanceState *state)
{
    u8 first = state->first;
    u8 second = state->second;

    if (first >= second)
    {
        if ((first >> 1) >= second)
        {
            state->mask = 0x0F;
            goto single_channel;
        }
    }
    else if ((second >> 1) >= first)
    {
        state->mask = 0xF0;
        goto single_channel;
    }
    state->mask = 0xFF;
    state->intensity = ((u32)state->second + state->first) >> 4;
    goto scale_intensity;

single_channel:
    state->intensity = ((u32)state->second + state->first) >> 4;
    if (state->intensity > 15)
        state->intensity = 15;

scale_intensity:
    state->scaled = (state->strength * state->intensity + 15) >> 4;
    state->mask &= state->allowed_mask;
}
