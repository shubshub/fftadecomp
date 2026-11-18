#include "control_flags.h"

/* Both axes interpolate signed coordinates with the same bounds check,
 * at 0x0813DD9A and 0x0813DDB8. */
static inline s32 interpolate(s16 first, s16 last, u16 duration, u16 elapsed)
{
    if (elapsed >= duration)
        return last;
    return first + (last - first) * elapsed / duration;
}

/* Complete target [0x0813DD58, 0x0813DE38), 224 bytes. */
s32 func_0813DD58(u8 layer, u16 duration, u16 elapsed, u16 first_x,
                  u16 first_y, u16 last_x, u16 last_y)
{
    u16 x;
    u16 y;

    if (duration <= elapsed)
        return 0;
    x = interpolate(first_x, last_x, duration, elapsed);
    y = interpolate(first_y, last_y, duration, elapsed);
    switch (layer) {
    case 0:
        g_control_flags_03000940.bg0hofs = x;
        g_control_flags_03000940.bg0vofs = y;
        break;
    case 1:
        g_control_flags_03000940.bg1hofs = x;
        g_control_flags_03000940.bg1vofs = y;
        break;
    case 2:
        g_control_flags_03000940.bg2hofs = x;
        g_control_flags_03000940.bg2vofs = y;
        break;
    case 3:
        g_control_flags_03000940.bg3hofs = x;
        g_control_flags_03000940.bg3vofs = y;
        break;
    }
    return 1;
}
