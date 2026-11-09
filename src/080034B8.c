#include "control_flags.h"

/* 080034B8..08003508: 80 bytes. */
void func_080034B8(u16 control, u8 layer)
{
    if (layer == 0)
        g_control_flags_03000940.bg0cnt = control;
    else if (layer == 1)
        g_control_flags_03000940.bg1cnt = control;
    else if (layer == 2)
        g_control_flags_03000940.bg2cnt = control;
    else
        g_control_flags_03000940.bg3cnt = control;
}
