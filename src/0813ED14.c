#include "control_flags.h"

/* Complete target: [0x0813ED14, 0x0813EDA0), 140 bytes. */
void func_0813ED14(u16 duration, u16 elapsed, u8 first_low, u8 first_high,
                   u8 last_low, u8 last_high)
{
    if (duration <= elapsed) {
        g_control_flags_03000940.bldalpha_lo = last_low;
        g_control_flags_03000940.bldalpha_hi = last_high;
    } else {
        g_control_flags_03000940.bldalpha_lo =
            first_low + (last_low - first_low) * elapsed / duration;
        g_control_flags_03000940.bldalpha_hi =
            first_high + (last_high - first_high) * elapsed / duration;
    }
}
