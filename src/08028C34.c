#include "control_flags.h"

/* 08028C34..08028C84: 80 bytes. */
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);

void func_08028C34(void)
{
    g_control_flags_03000940.winin_hi = 0x13;
    g_control_flags_03000940.win1h_hi = 0x10;
    g_control_flags_03000940.win1v_hi = 8;
    g_control_flags_03000940.win1h_lo = 0xE0;
    g_control_flags_03000940.win1v_lo = 0x20;
    g_control_flags_03000940.display |= 0x4000;
    func_0802A2C0(2, 2, 0x1A, 6);
}
