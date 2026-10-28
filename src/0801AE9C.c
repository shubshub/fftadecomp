#include "ffta.h"

typedef struct State0801AE9C {
    u8 unknown_0000[0x2FC2];
    u8 flags;
} State0801AE9C;

extern State0801AE9C g_state_02000000;

/* Complete [0x0801AE9C, 0x0801AECA): 46 bytes, 18 instructions. */
u32 func_0801AE9C(void)
{
    u8 mode = g_state_02000000.flags & 3;

    if (mode == 2)
        return 1;
    if (mode == 1)
        return 2;
    return 0;
}
