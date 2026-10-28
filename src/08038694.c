#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} State08038694;

extern State08038694 g_state_02000000;

/* Complete [0x08038694, 0x080386C8): 52 bytes, 22 instructions. */
u8 func_08038694(u16 value)
{
    s32 index;

    for (index = 0; index < 20; index++) {
        if (g_state_02000000.entries[index] == value) {
            g_state_02000000.entries[index] = 0;
            return 1;
        }
    }
    return 0;
}
