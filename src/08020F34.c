#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01[0x2B];
} InitializationEntry;

typedef struct {
    u16 value_00;
    u8 unknown_02[2];
    InitializationEntry entries[4];
} InitializationState;

extern InitializationState *g_state_0200F1D4;

void func_08020F34(InitializationState *state)
{
    u8 index;

    state->value_00 = 0x400;
    for (index = 0; index < 4; index++)
        state->entries[index].value = 0;
    g_state_0200F1D4 = state;
}
