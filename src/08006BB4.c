/* 0x08006BB4 - 42 bytes
 * Target: 00b5 011c 0020 0880 ff20 c870 8878 421e 002a 08db 8968 0023
 *         9000 4018 0360 0438 013a 002a fada 01bc 0047
 */
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

void func_08006BB4(RunnerState *state)
{
    int index;

    state->field_00 = 0;
    state->field_03 = 0xFF;
    for (index = state->field_02 - 1; index >= 0; index--) {
        state->words[index] = 0;
    }
}
