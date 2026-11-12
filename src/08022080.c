#include "ffta.h"

/* 0x08022080 - 18 bytes.
 * Target: c1000918c90040014018fa21890040187047
 */
u32 func_08022080(u32 value)
{
    u32 scaled = value * 72;

    value <<= 5;
    return value + scaled + 1000;
}
