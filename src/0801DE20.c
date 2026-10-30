#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
    u8 unknown_2E[0x1EA];
    u8 first_ready;
    u8 unknown_219[3];
    u8 second_ready;
} ReadinessState0801DE20;

extern ReadinessState0801DE20 g_state_02007F40;

/* Complete [0x0801DE20, 0x0801DE88): 104 bytes, 48 instructions. */
void func_0801DE20(u8 mode)
{
    if (mode == 1 || mode == 3)
        g_state_02007F40.first_ready = 0;
    if (mode == 2 || mode == 3)
        g_state_02007F40.second_ready = 0;
    if (g_state_02007F40.first_ready == 0 && g_state_02007F40.second_ready == 0)
        g_state_02007F40.flags &= ~0x400;
    g_state_02007F40.flags |= 0x200;
}
