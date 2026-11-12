#include "control_flags.h"

/* 0x0802A2C0 - 176 bytes including the complete literal pools.
 * Configure window 0 in tile coordinates, or disable an empty window. */
void func_0802A2C0(u8 x, u8 y, u8 width, u8 height)
{
    if (x == 0 && width == 0 && height == 0) {
        g_control_flags_03000940.display &= ~0x2000;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_lo = 0;
        g_control_flags_03000940.winin_lo = 0;
    } else {
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.winin_lo = 0x1F;
        g_control_flags_03000940.win0h_hi = x * 8;
        g_control_flags_03000940.win0v_hi = y * 8;
        g_control_flags_03000940.win0h_lo = (x + width) * 8;
        g_control_flags_03000940.win0v_lo = (y + height) * 8;
        g_control_flags_03000940.display |= 0x2000;
    }
}
