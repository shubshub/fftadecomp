#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u32 flags_04;
    u8 unknown_08[0x1c];
    u16 value_24;
    u16 value_26;
    u16 state_28;
    u8 unknown_2a[0x0a];
    u32 signature_34;
} State08145388;

/* 0x08145388 - 40 bytes including two literal words.
 * Target: 021c0904090c536b0548834207d1d18491840220108550680249084050607047536d7368ffffff7f
 */
void func_08145388(State08145388 *state, u16 value)
{
    if (state->signature_34 == 0x68736D53) {
        state->value_26 = value;
        state->value_24 = value;
        state->state_28 = 2;
        state->flags_04 &= 0x7FFFFFFF;
    }
}
