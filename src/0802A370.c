#include "control_flags.h"

/* Complete body 0x0802A370..0x0802A424: 180 bytes including literal pools. */
void func_0802A370(u8 x, u8 y, u8 width, u8 height)
{
    if (x == 0 && y == 0 && width == 0 && height == 0) {
        g_control_flags_03000940.display &= 0xBFFF;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_lo = 0;
        g_control_flags_03000940.winin_hi = 0;
    } else {
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.winin_hi = 0x1F;
        g_control_flags_03000940.win1h_hi = x * 8;
        g_control_flags_03000940.win1v_hi = y * 8;
        g_control_flags_03000940.win1h_lo = (x + width) * 8;
        g_control_flags_03000940.win1v_lo = (y + height) * 8;
        g_control_flags_03000940.display |= 0x4000;
    }
}
