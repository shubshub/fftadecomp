#include "control_flags.h"

/* Complete [0x0802A4B4, 0x0802A534): 128 bytes, including the control literal. */
void func_0802A4B4(u8 right, u8 bottom, u8 left, u8 top)
{
    g_control_flags_03000940.winout_lo = 0x1f;
    g_control_flags_03000940.winin_lo = 0x3f;
    g_control_flags_03000940.bldcnt_lo = 0x48;
    g_control_flags_03000940.bldcnt_hi = 0x33;
    g_control_flags_03000940.bldalpha_lo = 0x0e;
    g_control_flags_03000940.bldalpha_hi = 0x09;
    g_control_flags_03000940.win0h_hi = right;
    g_control_flags_03000940.win0v_hi = bottom;
    g_control_flags_03000940.win0h_lo = left;
    g_control_flags_03000940.win0v_lo = top;
    g_control_flags_03000940.display |= 0x2000;
}
