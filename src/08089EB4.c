#include "ffta.h"

/* Complete [0x08089EB4, 0x08089F20): 108 bytes, 54 instructions. */
void func_08089EB4(u16 *dest, u16 tile, u16 width, u16 height, u16 flags)
{
    s32 y;
    for (y = 0; y < height; y++) {
        s32 x;
        for (x = 0; x < width; ) {
            dest[x] = tile | flags;
            dest[x + 0x20] = (tile + 1) | flags;
            x++;
            tile += 2;
        }
        dest += 0x40;
    }
}
