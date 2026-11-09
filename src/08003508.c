#include "control_flags.h"

/* 08003508..08003558: 80 bytes. */
void func_08003508(u16 value, u8 channel)
{
    if (channel == 0)
        g_control_flags_03000940.bg0hofs = value;
    else if (channel == 1)
        g_control_flags_03000940.bg1hofs = value;
    else if (channel == 2)
        g_control_flags_03000940.bg2hofs = value;
    else
        g_control_flags_03000940.bg3hofs = value;
}
