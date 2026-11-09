#include "control_flags.h"

/* 08028BDC..08028C34: 88 bytes. */
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);

void func_08028BDC(void)
{
    func_0802A370(0, 0, 0, 0);
    g_control_flags_03000940.winout_lo = 0x1F;
    g_control_flags_03000940.winin_lo = 0x3F;
    g_control_flags_03000940.win0h_hi = 0x88;
    g_control_flags_03000940.win0v_hi = 0x30;
    g_control_flags_03000940.win0h_lo = 0xF8;
    g_control_flags_03000940.win0v_lo = 0x90;
    g_control_flags_03000940.display |= 0x2000;
}
