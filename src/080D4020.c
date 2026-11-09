#include "control_flags.h"

/* 0x080D4020..0x080D4038: 24 bytes. */
void func_080D4020(void)
{
    g_control_flags_03000940.bldcnt_lo = 0;
    g_control_flags_03000940.bldcnt_hi = 0;
}
