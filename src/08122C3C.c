#include "control_flags.h"

u32 func_08122C3C(void *state, const u8 *command)
{
    g_control_flags_03000940.bldcnt_lo = 0;
    g_control_flags_03000940.bldcnt_hi = 3;
    g_control_flags_03000940.bldalpha_lo = 16;
    g_control_flags_03000940.bldalpha_hi = 0;
    return 0x100;
}
