#include "control_flags.h"

/* 08009728..0800975C: 52 bytes. */
void func_08009728(void)
{
    g_control_flags_03000940.display &= ~0x2000;
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_lo = 0;
}
