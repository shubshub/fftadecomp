#include "control_flags.h"

extern u8 func_0801D880(void);
extern u8 g_state_02000000[];

/* Complete body 0x08022B24..0x08022BA2: 126 bytes including middle pools. */
void func_08022B24(void)
{
    if (func_0801D880()) {
        g_control_flags_03000940.bldcnt_lo = 0x43;
        g_control_flags_03000940.bldcnt_hi = 0x3F;
    } else {
        g_control_flags_03000940.bldcnt_lo = 0x48;
        g_control_flags_03000940.bldcnt_hi = 0x33;
    }
    if ((g_state_02000000[0x2FC2] & 3) == 2) {
        g_control_flags_03000940.bldalpha_lo = 13;
        g_control_flags_03000940.bldalpha_hi = 7;
    } else {
        g_control_flags_03000940.bldalpha_lo = 14;
        g_control_flags_03000940.bldalpha_hi = 9;
    }
}
