#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16;
    u8 height;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
} TilePanel;

/* Complete target: 0x08040D3C..0x08040DA2, 102 bytes. */
void func_08040D3C(TilePanel *panel)
{
    u16 *row = panel->tiles;
    u16 tile = (panel->palette << 12) + panel->first_tile;
    s32 width = panel->width;
    s32 rows = panel->height;

    for (; rows > 0; rows--)
    {
        u16 *destination = row;
        s32 x;

        for (x = 0; x < width; x++)
        {
            *destination = tile++;
            destination[panel->width] = tile++;
            destination++;
        }
        row += panel->width * 2;
    }
}
