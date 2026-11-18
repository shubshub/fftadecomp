#include "ffta.h"

/* [0x080D6798, 0x080D694E), 438 bytes. */
extern u16 func_080D663C(const u16 **cursor, u16 *index, u8 encoded);

static inline u16 adjust_tile(u16 tile, s16 base, s16 palette)
{
    s16 number = tile & 0x3FF;
    u32 bank;
    u16 flip;

    if (number == 0x3FF)
        return tile;
    bank = (tile & 0xF000) >> 12;
    flip = tile & 0xC00;
    number += base;
    tile = number | ((bank + palette) << 12);
    return tile | flip;
}

void func_080D6798(u16 *destination, s16 x, s16 y, const u16 *source,
                   u8 width, u8 height, u16 base, u8 palette,
                   u8 flipX, u8 flipY, u8 encoded)
{
    u16 index = 0;
    u16 flip = 0;
    s16 ox;
    s16 oy;
    s16 dx = 1;
    s16 dy = 1;
    u8 i;
    u8 j;

    if (flipX) {
        flip = 0x400;
        dx = -1;
        x += width - 1;
    }
    if (flipY) {
        flip |= 0x800;
        dy = -1;
        y += height - 1;
    }

    for (i = 0, oy = 0; i < height; i++, oy += dy) {
        s16 py = y + oy;
        u16 *line;

        if (py < 0)
            continue;
        if (py > 31)
            continue;
        line = destination + py * 32;
        for (j = 0, ox = 0; j < width; j++, ox += dx) {
            s16 px = x + ox;
            u16 *cell;
            u16 value;

            if (px < 0)
                continue;
            if (px > 31)
                continue;
            cell = &line[px];
            value = func_080D663C(&source, &index, encoded);
            if (base != 0 || palette != 0)
                value = adjust_tile(value, base, palette);
            *cell = value ^ flip;
        }
    }
}
