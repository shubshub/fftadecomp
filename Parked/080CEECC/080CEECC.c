#include "ffta.h"

extern u8 g_state_02000000[];

u32 func_080CE4DC(u16 index, u8 selector);

u32 func_080CEECC(u16 index)
{
    u16 required = func_080CE4DC(index, 42);
    s32 slot;

    if (required != 0) {
        for (slot = 0; slot < 64; slot++) {
            if (g_state_02000000[0x2B08 + slot * 4] == required)
                break;
        }
        if (slot == 64)
            return 0;
    }
    required = func_080CE4DC(index, 44);
    if (required != 0) {
        for (slot = 0; slot < 64; slot++) {
            if (g_state_02000000[0x2B08 + slot * 4] == required)
                break;
        }
        if (slot == 64)
            return 0;
    }
    required = func_080CE4DC(index, 46);
    if (required != 0) {
        u8 quantity = g_state_02000000[0x21B4 + required * 2];

        if (quantity < func_080CE4DC(index, 47))
            return 0;
    }
    return 1;
}
