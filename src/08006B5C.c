/* 0x08006B5C - 48 bytes
 * Target: 10b5 031c 0020 1880 ff20 d870 9878 421e 002a 08db 9968 0024
 *         9000 4018 0460 0438 013a 002a fada 0020 9870 10bc 01bc 0047
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

void func_08006B5C(RunnerState *state)
{
    int index;

    state->field_00 = 0;
    state->field_03 = 0xFF;
    for (index = state->field_02 - 1; index >= 0; index--) {
        state->words[index] = 0;
    }
    state->field_02 = 0;
}
