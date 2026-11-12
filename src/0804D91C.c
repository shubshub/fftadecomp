#include "control_flags.h"

/* Complete [0x0804D91C, 0x0804D9D0): 180 bytes including literal pools. */
void func_0804D91C(u8 x, u8 y, u8 width, u8 height)
{
    if (x == 0 && width == 0 && height == 0) {
        g_control_flags_03000940.display &= 0xDFFF;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_lo = 0;
        g_control_flags_03000940.winout_lo = 0;
        g_control_flags_03000940.winin_lo = 0;
    } else {
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.winin_lo = 0x1F;
        g_control_flags_03000940.win0h_hi = x << 3;
        g_control_flags_03000940.win0v_hi = y << 3;
        g_control_flags_03000940.win0h_lo = (x + width) << 3;
        g_control_flags_03000940.win0v_lo = (y + height) << 3;
        g_control_flags_03000940.display |= 0x2000;
    }
}
