#include "ffta.h"

/* Complete target [0x08081960, 0x080819EE): 142 bytes, 71 instructions.
 * f0b5474680b4071cf8688446f87f0003b98b40180004040cbe8bfa7d002a31d0
 * 60460680701c61464880787d40006044b11c0180787d40006044f11c4180201d
 * 0004040c301c26300004060c013a9046634604331025211c481c0004040c221c
 * 1980797d4900c918501c0004040c0a800233013d002deeda787d800084444246
 * 002acdd108bc9846f0bc01bc0047
 */

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
} TileWindow;

void func_08081960(TileWindow *window)
{
    u16 *row = window->tiles;
    u16 tile = (window->palette << 12) + window->first_tile;
    u16 border = window->first_tile;
    s32 remaining;
    s32 column;

    for (remaining = window->rows; remaining != 0; remaining--) {
        row[0] = border;
        row[1] = border + 1;
        row[window->stride] = border + 2;
        row[window->stride + 1] = border + 3;
        tile += 4;
        border += 0x26;
        for (column = 0; column < 17; column++) {
            u16 *cursor = &row[column + 2];

            cursor[0] = tile++;
            cursor[window->stride] = tile++;
        }
        row += window->stride * 2;
    }
}
