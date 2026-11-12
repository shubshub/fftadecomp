#include "control_flags.h"

/* Complete [0x0813ECC4, 0x0813ED14): 80 bytes, including both literal words. */
void func_0813ECC4(u16 first, u16 second)
{
    if (first >= second) {
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 16;
    } else {
        g_control_flags_03000940.bldalpha_hi = (second * 16) / first;
        g_control_flags_03000940.bldalpha_lo =
            16 - g_control_flags_03000940.bldalpha_hi;
    }
}
