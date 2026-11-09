#include "control_flags.h"

/* 08122C6C..08122CA8 (60 bytes) */
int func_08122C6C(void)
{
    g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
    g_control_flags_03000940.bldalpha_lo = (g_control_flags_03000940.bldalpha_hi = 0);
    return 0x100;
}
