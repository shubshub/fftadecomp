#include "ffta.h"

typedef struct ReadinessState {
    u8 unknown_00[0x2C];
    u16 flags;
    u8 unknown_2E[0x1EA];
    u8 first_ready;
    u8 unknown_219[3];
    u8 second_ready;
} ReadinessState;

extern ReadinessState g_state_02007F40;

/* 0801DF8C..0801DFDA: 78 bytes, 37 instructions. */
u8 func_0801DF8C(u8 mode)
{
    if (!(g_state_02007F40.flags & 0x400))
        return 0;
    if ((mode == 1 || mode == 3) && !g_state_02007F40.first_ready)
        return 0;
    if ((mode == 2 || mode == 3) && !g_state_02007F40.second_ready)
        return 0;
    return 1;
}
