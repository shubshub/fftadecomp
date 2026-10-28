#include "ffta.h"

typedef struct UpdateState {
    u8 unknown_00[0x16];
    u16 value;
    u16 accumulator;
    u8 unknown_1A[0x0E];
    u8 active;
} UpdateState;

extern UpdateState *data_0200918C;
extern u8 g_state_02000000[];

/* 080133B0..08013404: 84 bytes, 37 instructions. */
void func_080133B0(u16 value)
{
    data_0200918C->value = value ? value : 1;
    if ((g_state_02000000[0x2FC0] & 0x18) == 8)
        data_0200918C->value = 0x1000;
    if (data_0200918C->value == 0x1000) {
        data_0200918C->accumulator = 0x8000;
        data_0200918C->active = 1;
    }
}
