#include "control_flags.h"

/* Complete body 0x0802A424..0x0802A4B4: 144 bytes including literal pools. */
void func_0802A424(u8 x, u8 y, u8 width, u8 height)
{
    if (x == 0 && y == 0 && width == 0 && height == 0) {
        g_control_flags_03000940.display &= 0xDFFF;
    } else {
        g_control_flags_03000940.winout_lo = 0x1F;
        g_control_flags_03000940.winin_lo = 0x3F;
        g_control_flags_03000940.win0h_hi = x * 8;
        g_control_flags_03000940.win0v_hi = y * 8;
        g_control_flags_03000940.win0h_lo = (x + width) * 8;
        g_control_flags_03000940.win0v_lo = (y + height) * 8;
        g_control_flags_03000940.display |= 0x2000;
    }
}
