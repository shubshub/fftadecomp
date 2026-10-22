#include "ffta.h"

typedef struct RunnerState {
    u16 field_00;
    u8 field_02;
    u8 field_03;
    u8 field_04;
    u8 field_05;
    u8 unknown_06[2];
    u32 *words;
    u8 *flags;
} RunnerState;

void func_08006A7C(RunnerState *state, u32 *words, u8 *flags, u8 count)
{
    int index;

    state->field_00 = 0;
    state->field_04 = 0;
    state->field_05 = 0;
    state->field_02 = count;
    state->field_03 = 0xFF;
    state->words = words;
    state->flags = flags;
    for (index = state->field_02 - 1; index >= 0; index--) {
        state->words[index] = 0;
        state->flags[index] = 0;
    }
}
