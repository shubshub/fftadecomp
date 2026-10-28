#include "ffta.h"

/* Target: complete [0x080386C8, 0x08038704), 60 bytes, 25 instructions. */
typedef struct {
    u8 unknown_00[0x1f3c];
    u16 values[20];
} State02000000;

extern State02000000 g_state_02000000;

s32 func_080386C8(u16 value, s32 limit)
{
    s32 count = 0;
    s32 i;

    for (i = 0; i < 20; i++) {
        if (g_state_02000000.values[i] == value) {
            g_state_02000000.values[i] = 0;
            count++;
            if (count >= limit)
                break;
        }
    }
    return count;
}
