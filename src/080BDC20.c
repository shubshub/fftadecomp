#include "ffta.h"

/* 0x080BDC20..0x080BDC42: 34 bytes, 17 Thumb instructions. */
u32 func_080BDC20(const u8 *grid, u8 x, u8 y)
{
    u32 offset = x * 4 + y * 64;
    u32 value = *(const u32 *)(grid + offset);
    if (value == (u32)-1) {
        return 0;
    }
    return value;
}
