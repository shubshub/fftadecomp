#include "ffta.h"

/* 0x0812F0CC..0x0812F0D6: 10 bytes, 4 instructions. */
extern u32 func_0812E4F4(const void *unit, u16 *output);

u32 func_0812F0CC(const void *unit, u16 *output)
{
    return func_0812E4F4(unit, output);
}
