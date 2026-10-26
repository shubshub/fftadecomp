#include "ffta.h"

/* 0x0808B66C..0x0808B758: 236 bytes. */
typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileSurface;

typedef struct {
    u8 x;
    u8 y;
    u8 palette;
    s8 shape;
    u16 tile;
    u8 unknown_06[2];
} TileEntry;

typedef struct {
    u16 count;
    u16 unknown_02;
    const TileEntry *entries;
} TileList;

extern TileSurface data_030009E0[];

void func_0808B66C(s32 surface, const TileList *list, s32 x, s32 y)
{
    s32 index = 0;

    if (index < list->count) {
        const TileEntry *entries = list->entries;
        do {
            const TileEntry *entry = &entries[index];
            s8 shape = entry->shape;
            u16 width;
            u16 height;
            u16 tile;
            u16 *tiles;
            u16 row;

            if (entry->shape >= 0) {
                width = entries[index].shape;
                height = 1;
            } else {
                width = shape & 0x0F;
                height = (shape & 0x70) >> 4;
            }

            tile = (entries[index].palette << 12) | entries[index].tile;
            tiles = data_030009E0[surface].tiles;
            tiles += entries[index].x + x;
            tiles += (entries[index].y + y) * data_030009E0[surface].stride;

            for (row = 0; row < height; ++row) {
                u16 column;
                for (column = 0; column < width; ++column)
                    tiles[column] = tile + column;
                tiles += data_030009E0[surface].stride;
            }
        } while (++index < list->count);
    }
}
