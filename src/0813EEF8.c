#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x11AC];
    u32 value;
    u16 count;
    u8 unknown_11B2[2];
    u32 position;
    u8 active;
} State0813EEF8;

void func_0813EEF8(State0813EEF8 *state, u32 value)
{
    state->count = 0;
    state->position = 0;
    state->active = 1;
    state->value = value;
}
