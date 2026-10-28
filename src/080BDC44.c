#include "ffta.h"

/* 0x080BDC44..0x080BDC56: 18 bytes. */
void func_080BDC44(u8 *grid, u8 x, u8 y)
{
    u32 offset = x * sizeof(u32) + y * (16 * sizeof(u32));

    *(u32 *)(grid + offset) = 0;
}
