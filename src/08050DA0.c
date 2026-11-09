#include "control_flags.h"

/* 0x08050DA0..0x08050DE8: 72 bytes, including two literal words. */
extern void func_0804D91C(u32, u32, u32, u32);

void func_08050DA0(void)
{
    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.win1h_lo = 0;
    g_control_flags_03000940.win1v_lo = 0;
    g_control_flags_03000940.display &= 0xBFFF;
    func_0804D91C(0, 1, 0x1E, 2);
}
