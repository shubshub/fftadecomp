#include "ffta.h"

/* 0x0801AD1C..0x0801AD38: 28 bytes. */
extern u8 data_020091A0[];

u8 *func_0801AD1C(u8 selector)
{
    u8 *buffer = data_020091A0;

    if (selector)
        buffer += 0x2000;
    return buffer;
}
