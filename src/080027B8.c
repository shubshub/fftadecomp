#include "ffta.h"

/* 0x080027B8..0x080027E4: 44 bytes / 22 instructions. */
u16 func_080027B8(const u8 *data, u16 count)
{
    u16 sum = 0;
    u16 index;

    for (index = 0; index < count; ++index)
        sum += *data++;
    return sum;
}
