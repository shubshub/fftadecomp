#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[4];
    u16 tiles[80];
} Panel0806F050;

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid;

extern TileGrid data_030008B0;
extern TileGrid data_03000990;
extern void func_0802B4A8(TileGrid *grid, s32 x, s32 y,
                          const u16 *source, u8 width, u8 height);

/* Complete target: [0x0806F050, 0x0806F0D4), 132 bytes, 59 instructions. */
void func_0806F050(Panel0806F050 *panel, u8 x, u8 y)
{
    u8 row;
    u8 column;

    panel->x = x;
    panel->y = y;
    func_0802B4A8(&data_030008B0, panel->x, panel->y, panel->tiles, 10, 8);
    for (row = 0; row < 8; row++) {
        u16 row_offset = ((s8)y + row) * 32;

        for (column = 0; column < 14; column++) {
            if ((u32)((s8)x + column) <= 31)
                data_03000990.tiles[row_offset + column + (s8)x] = 0xC001;
        }
    }
}
