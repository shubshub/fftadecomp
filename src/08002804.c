#include "ffta.h"

extern u32 g_state_030034B0;

u32 func_08002804(void)
{
    g_state_030034B0 = g_state_030034B0 * 0x41C64E6D + 0x3039;
    return (g_state_030034B0 >> 16) & 0x7FFF;
}
