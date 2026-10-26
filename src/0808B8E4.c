#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

extern TileRenderer data_030009E0[];

u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y)
{
    u16 *tiles;

    if (plane)
        tiles = data_030009E0[index].second_plane + x
            + data_030009E0[index].stride * y;
    else
        tiles = data_030009E0[index].first_plane + x
            + data_030009E0[index].stride * y;
    return tiles;
}
