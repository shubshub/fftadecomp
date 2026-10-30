#include "ffta.h"

/* 0x0808A008 .. 0x0808A084: 124 bytes, including literal pool. */
void func_0808A008(u16 *tiles, u16 start, u16 stride, u16 end,
                   u16 height, u16 flags)
{
    int row;
    int column;

    for (row = 0; row < height; row++) {
        for (column = start; column < end; column++)
            tiles[column] = (tiles[column] & 0x0FFF) | flags;
        tiles += stride;
    }
}
