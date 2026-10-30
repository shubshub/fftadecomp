/* Target bytes (220):
 * 10 b5 04 1c 20 79 02 28 35 d0 02 28 04 dc 00 28
 * 60 d0 01 28 0a d0 5e e0 0a 28 5c d0 0a 28 02 dc
 * 03 28 3c d0 57 e0 64 28 51 d0 54 e0 20 76 60 71
 * e0 88 01 30 e0 80 c0 21 89 00 e3 88 50 20 0a 22
 * 00 f0 82 f8 e0 82 a0 82 0c 21 60 5e 10 22 a1 5e
 * e3 88 0a 22 00 f0 78 f8 20 81 0e 21 60 5e 12 22
 * a1 5e e3 88 0a 22 00 f0 6f f8 60 81 e0 88 09 28
 * 31 d9 02 20 27 e0 01 20 60 71 20 76 e0 88 01 30
 * e0 80 c0 20 80 00 80 21 49 00 e3 88 0a 22 00 f0
 * 5b f8 e0 82 a0 82 e0 88 0a 28 1c d9 12 e0 e0 88
 * 01 30 e0 80 e0 88 e2 89 12 06 12 14 63 8a 1b 06
 * 1b 14 32 21 00 f0 3a fc 00 04 00 16 60 81 e0 88
 * 32 28 08 d9 64 20 20 71 00 20 e0 80 03 e0 00 20
 * 60 71 01 20 20 76 10 bc 01 bc 00 47
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 phase;
    u8 field_05;
    u16 counter;
    s16 field_08;
    s16 field_0A;
    s16 field_0C;
    s16 field_0E;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
    u8 field_18;
} State08136868;

extern s32 func_081369B0(s32 start, s32 end, u32 duration, u32 elapsed);
extern s32 func_08137194(u32 elapsed, u32 duration, s32 start, s32 end);

void func_08136868(State08136868 *state)
{
    switch (state->phase) {
    case 1:
        state->field_18 = 1;
        state->field_05 = 1;
        state->counter++;
        state->field_14 = state->field_16 =
            func_081369B0(80, 768, 10, state->counter);
        state->field_08 = func_081369B0(state->field_0C, state->field_10,
                                      10, state->counter);
        state->field_0A = func_081369B0(state->field_0E, state->field_12,
                                      10, state->counter);
        if (state->counter > 9) {
            state->phase = 2;
            state->counter = 0;
        }
        break;
    case 2:
        state->field_05 = 1;
        state->field_18 = 1;
        state->counter++;
        state->field_14 = state->field_16 =
            func_081369B0(768, 256, 10, state->counter);
        if (state->counter > 10) {
            state->phase = 100;
            state->counter = 0;
        }
        break;
    case 3:
        state->counter++;
        state->field_0A = (s16)func_08137194(
            state->counter, 50, (s16)((u16)state->field_0E << 8),
            (s16)((u16)state->field_12 << 8)) >> 8;
        if (state->counter > 50) {
            state->phase = 100;
            state->counter = 0;
        }
        break;
    case 100:
        state->field_05 = 0;
        state->field_18 = 1;
        break;
    case 0:
        state->field_18 = 0;
        break;
    case 10:
    default:
        break;
    }
}

