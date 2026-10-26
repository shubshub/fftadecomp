#include "ffta.h"

typedef struct {
    u8 unknown_00[0xc];
    u16 *tiles;
    u8 unknown_10[5];
    u8 row_width;
    u8 unknown_16;
    u8 row_pairs;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1e;
    u8 palette;
} TileRows08042CB4;

void func_08042CB4(TileRows08042CB4 *rows)
{
    u16 *top = rows->tiles;
    u16 tile = (rows->palette << 12) + rows->first_tile;
    s32 width = rows->row_width;
    s32 pairs = rows->row_pairs;

    if (pairs != 0) {
        u16 *bottom = top + width;
        do {
            s32 column;

            top[0] = tile++;
            top[1] = tile++;
            bottom[0] = tile++;
            bottom[1] = tile++;
            for (column = 2; column < 13; column++) {
                top[column] = tile++;
                bottom[column] = tile++;
            }
            bottom += width * 2;
            top += width * 2;
        } while (--pairs != 0);
    }
}
