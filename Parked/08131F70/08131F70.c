#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F64];
    u32 value;
} AdjustmentState;

extern AdjustmentState g_state_02000000;

u8 func_08131BB8(void *record);

void func_08131F70(u8 *object)
{
    u16 flags = *(u16 *)(object + 0x26) & 0x10;
    s32 amount;
    u32 remaining;

    if (flags == 0) {
        amount = ((s16 *)(object + 0x20))[object[0x28]];
        if (amount < 0)
            amount = -amount;
        if (func_08131BB8(*(void **)(object + 8))) {
            if (func_08131BB8(*(void **)(object + 8))) {
                remaining = g_state_02000000.value - amount;
                if ((s32)remaining <= 0)
                    g_state_02000000.value = 0;
                else
                    g_state_02000000.value = remaining;
            }
        }
    }
}
