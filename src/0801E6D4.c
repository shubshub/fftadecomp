#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u8 first;
    u8 second;
} State0801E6D4;

extern State0801E6D4 g_state_02007F40;

/* 0801E6D4..0801E6E4: 02 4B 1A 7F 02 70 58 7F 08 70 70 47 40 7F 00 02. */
void func_0801E6D4(u8 *first, u8 *second)
{
    State0801E6D4 *state = &g_state_02007F40;

    *first = state->first;
    *second = state->second;
}
