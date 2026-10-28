#include "ffta.h"

extern u8 data_0200D1A0[];

/* 0801AD38..0801AD54: 28 bytes, 11 instructions. */
u8 *func_0801AD38(u8 second)
{
    u8 *buffer = data_0200D1A0;

    if (second)
        buffer += 0x1000;
    return buffer;
}
