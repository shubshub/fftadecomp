#include "control_flags.h"

/* 0x0802A534 - 152 bytes including the complete literal pool.
 * Reset window masks, blending and bounds, then disable both windows. */
void func_0802A534(void)
{
    g_control_flags_03000940.winout_lo = 0;
    g_control_flags_03000940.winin_lo = 0;
    g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
    g_control_flags_03000940.bldalpha_lo = (g_control_flags_03000940.bldalpha_hi = 0);
    g_control_flags_03000940.win0h_hi = (g_control_flags_03000940.win0v_hi = 0);
    g_control_flags_03000940.win0h_lo = (g_control_flags_03000940.win0v_lo = 0);
    g_control_flags_03000940.win1h_hi = (g_control_flags_03000940.win1v_hi = 0);
    g_control_flags_03000940.win1h_lo = (g_control_flags_03000940.win1v_lo = 0);
    g_control_flags_03000940.display &= ~0x2000;
    g_control_flags_03000940.display &= ~0x4000;
}
