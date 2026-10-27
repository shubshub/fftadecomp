#include "ffta.h"

/* 0x0801B848..0x0801B878: 48 bytes. */
extern u16 *func_0801AD1C(u8 layer);

void func_0801B848(u8 layer, u16 x, u16 y, u16 value)
{
    u16 *tiles = func_0801AD1C(layer);

    if (x < 64 && y < 64) {
        tiles += y * 64 + x;
        *tiles = value;
    }
}
