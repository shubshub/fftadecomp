#include "ffta.h"

extern void func_0814186C(const void *source, void *destination, u32 control);

/* Clear up to two pixels on each of two rows in 4bpp tile data. Crossing
 * the right edge restarts at word zero of the next tile. At the bottom
 * edge the row base advances by 256 words, including after the last row. */
void func_0804BF78(u32 *tiles, u8 x, u8 y, u8 width, u8 height)
{
    u8 row = y & 7;
    u8 dy;

    for (dy = 0; dy < 2 && y + dy < height; ++dy) {
        u32 col = x;
        u32 *line = tiles + (row & 7);
        u8 dx;
        for (dx = 0; dx < 2 && x + dx < width; ++dx) {
            u32 input;

            col &= 7;
            func_0814186C(line, &input, 0x04000001);
            {
                volatile u32 fill = input & ~(15u << (col * 4));
                func_0814186C((const void *)&fill, line, 0x05000001);
            }
            if (++col > 7)
                line = tiles + 8;
        }
        if (++row > 7)
            tiles += 256;
    }
}
