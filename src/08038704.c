#include "ffta.h"

/* Target: complete [0x08038704, 0x08038734), 48 bytes, 20 instructions. */
typedef struct {
    u8 unknown_00[0x1f3c];
    u16 values[20];
} State02000000;

extern State02000000 g_state_02000000;

u32 func_08038704(u16 value)
{
    u32 count = 0;
    s32 i;

    for (i = 0; i < 20; i++) {
        if (g_state_02000000.values[i] == value)
            count++;
    }
    return count;
}
