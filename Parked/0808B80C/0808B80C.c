#include "ffta.h"

/* 0x0808B80C..0x0808B858: 76 bytes. */
typedef struct {
    u8 unknown_00[0x28];
    u8 stride;
    u8 unknown_29[0x23];
} TileSurface;

extern TileSurface data_030009E0[];

void func_0808B80C(s32 surface, u16 *tiles, u16 tile, u16 width,
                   u16 flags)
{
    u32 stride = data_030009E0[surface].stride;
    if (width != 0) {
        u32 remaining = width;
        do {
            tiles[0] = tile | flags;
            tiles[stride] = (tile + width) | flags;
            --remaining;
            ++tiles;
            ++tile;
        } while (remaining != 0);
    }
}
