#include "ffta.h"

typedef struct AudioState {
    u8 unknown_00[0x24];
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u8 unknown_2A[0x0A];
    u32 signature;
} AudioState;

/* Complete target: [0x0814511C, 0x0814513C), 32 bytes.
 * 021c0904090c536b0448834204d1d184918480204000108570470000536d7368
 */
void func_0814511C(AudioState *state, u16 interval)
{
    if (state->signature == 0x68736D53) {
        state->field_24 = state->field_26 = interval;
        state->field_28 = 0x100;
    }
}
