#include "control_flags.h"

/* Complete [0x0813EC74, 0x0813ECC4): 80 bytes, including both literal words. */
void func_0813EC74(u16 first, u16 second)
{
    if (first >= second) {
        g_control_flags_03000940.bldalpha_lo = 16;
        g_control_flags_03000940.bldalpha_hi = 0;
    } else {
        g_control_flags_03000940.bldalpha_lo = (second * 16) / first;
        g_control_flags_03000940.bldalpha_hi =
            16 - g_control_flags_03000940.bldalpha_lo;
    }
}
