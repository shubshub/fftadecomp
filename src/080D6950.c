#include "ffta.h"

extern u8 func_080D66F0(const u8 **stream, u16 *index, u8 encoded);

static inline u8 adjust_tile(u8 tile, s16 base)
{
    if (tile == 0xFF)
        return tile;
    return tile + base;
}

void func_080D6950(u16 *destination, s16 x, s16 y, const u8 *source,
                   u8 width, u8 height, u16 base, u8 encoded)
{
    u16 index = 0;
    s16 row;
    s16 column;

    for (row = 0; row < height; row++) {
        s16 py = y + row;
        u8 *line;

        if (py < 0)
            continue;
        if (py > 31)
            continue;
        line = (u8 *)destination + py * 32;
        for (column = 0; column < width; column++) {
            s16 px = x + column;
            u8 *cell;
            u16 value;

            if (px < 0)
                continue;
            if (px > 31)
                continue;
            cell = &line[px];
            value = func_080D66F0(&source, &index, encoded);
            if (base)
                value = adjust_tile(value, base);
            *cell = value;
        }
    }
}
