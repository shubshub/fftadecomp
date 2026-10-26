#include "ffta.h"

/* 0x0804BEE8..0x0804BF6E: 134 bytes. */
void func_0804BEE8(u8 *pixels, u8 x, u8 y, u8 color, u8 width, u8 height)
{
    u8 row = y & 7;

    if (y < height && x < width) {
        u8 shift = (x & 3) * 4;
        u16 mask = ~(15 << shift);
        u16 value = color << shift;
        u32 column = x & 0xFC;
        u8 *tile = pixels + ((column & 0xF8) << 2);
        u8 halfword = (column >> 1) & 3;
        u32 rowOffset;
        u8 tileRow;
        u16 stride;
        u16 *pixel;

        tile += halfword;
        rowOffset = row * 4;
        tileRow = y >> 3;
        stride = width * 4;
        pixel = (u16 *)(tile + (rowOffset + tileRow * stride));

        *pixel = (*pixel & mask) | value;
    }
}
