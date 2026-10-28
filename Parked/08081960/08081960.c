#include "ffta.h"

/* 0x08081960..0x080819EE: 142 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1e;
    u8 palette;
} TileWindow;

void func_08081960(TileWindow *window)
{
    u16 *row = window->tiles;
    u16 tile = (window->palette << 12) + window->first_tile;
    u16 *cursor;
    s32 column;
    u16 border = window->first_tile;
    u32 remaining = window->rows;

    for (; remaining != 0; --remaining) {
        row[0] = border;
        row[1] = border + 1;
        row[window->stride] = border + 2;
        row[window->stride + 1] = border + 3;
        tile += 4;
        border += 0x26;
        cursor = row + 2;
        for (column = 0x10; column >= 0; --column) {
            *cursor = tile++;
            cursor[window->stride] = tile++;
            ++cursor;
        }
        row += window->stride * 2;
    }
}
