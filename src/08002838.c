#include "ffta.h"

// 0x08002838-0x080028C8: 144 bytes, including the trailing literal pool.
// Four steps of the linear congruential generator, each reduced modulo
// range + 1, combined as (a + b - c - d) / 2.

extern u32 g_state_030034B0;

static inline u32 Random(void)
{
    g_state_030034B0 = g_state_030034B0 * 0x41C64E6D + 0x3039;
    return (g_state_030034B0 >> 16) & 0x7FFF;
}

s16 func_08002838(s32 range)
{
    s32 a = Random();
    s32 b = Random();
    s32 c = Random();
    s32 d = Random();

    range++;
    return (a % range + b % range - c % range - d % range) / 2;
}
