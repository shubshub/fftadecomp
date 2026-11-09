#include "control_flags.h"

/* 0x08003558..0x080035A8: 80 bytes / 30 instructions. */
void func_08003558(u16 value, u8 selector)
{
    if (selector == 0)
        g_control_flags_03000940.bg0vofs = value;
    else if (selector == 1)
        g_control_flags_03000940.bg1vofs = value;
    else if (selector == 2)
        g_control_flags_03000940.bg2vofs = value;
    else
        g_control_flags_03000940.bg3vofs = value;
}
