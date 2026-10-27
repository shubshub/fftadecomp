#include "ffta.h"

/* 0x0801B814..0x0801B848: 52 bytes. */
extern u16 *func_0801AD1C(u8 layer);

u16 func_0801B814(u8 layer, u16 x, u16 y)
{
    u16 *tiles = func_0801AD1C(layer);

    if (x >= 64 || y >= 64) {
        return 0xFFFF;
    }
    tiles += y * 64 + x;
    return *tiles;
}
