#include "ffta.h"

static inline void fill_row(u16 *destination, u32 count, u16 tile)
{
    while (count != 0) {
        *destination++ = tile;
        count--;
    }
}

/* Complete [0x08016560, 0x080165C4): 100 bytes, 50 instructions. */
void func_08016560(void *tiles, u8 width, u8 height, u16 flags,
                   u8 stride, u16 tile, u8 palette)
{
    if (width > 1 && height > 3) {
        u32 columns = width;
        u8 *row = (u8 *)tiles + stride * 4;
        u32 rows = (u16)(height - 3);

        tile += palette << 12;
        while (rows != 0) {
            rows--;
            fill_row((u16 *)row, columns, tile);
            row += stride * 2;
        }
    }
}
