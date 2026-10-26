#include "ffta.h"

extern const s8 data_0836D634[][4];

/* Target: [0x080165C4, 0x080167FE), 570 bytes, 280 instructions. */
void func_080165C4(u16 *tiles, u8 width, u8 height, u16 flags,
                   u8 stride, u16 base_tile, u16 fill_tile, u8 palette)
{
    u16 offset;
    u16 tile;
    s32 y;
    s32 x;
    s32 first;
    s32 last;

    if (height != 8)
        return;

    if (width > 4) {
        offset = 0;
        if (flags & 0x10) {
            first = 4;
            last = width;
        } else {
            first = 0;
            last = width - 4;
        }
        for (y = 0; y < height; y++) {
            if (y == 0)
                tile = base_tile + (palette << 12);
            else if (y == height - 1)
                tile = base_tile + (palette << 12) + 0x800;
            else
                tile = fill_tile + (palette << 12);
            for (x = first; x < last; x++)
                tiles[offset + x] = tile;
            offset += stride;
        }
    }

    tile = base_tile + (palette << 12);
    if (flags & 0x10) {
        u8 edge_width = width;

        if (edge_width > 4)
            edge_width = 4;
        offset = 0;
        tile += 0x400;
        {
            u32 fill = fill_tile + (palette << 12);

            for (y = 0; y < height; y++) {
                for (x = 0; x < edge_width; x++) {
                    s32 value;

                    if (y <= 3)
                        value = data_0836D634[y][x];
                    else
                        value = data_0836D634[height - (y + 1)][x];
                    if (value >= 0) {
                        s32 result = tile + value;

                        if (y > 3)
                            result += 0x800;
                        tiles[offset + x] = result;
                    } else if (value == -1) {
                        tiles[offset + x] = fill;
                    }
                }
                offset += stride;
            }
        }
    } else {
        if (width > 4) {
            last = 3;
            offset = width - 4;
        } else {
            last = width - 1;
            offset = 0;
        }
        {
            u32 fill = fill_tile + (palette << 12);

            for (y = 0; y < height; y++) {
                for (x = 0; x < last + 1; x++) {
                    s32 value;

                    if (y <= 3)
                        value = data_0836D634[y][x];
                    else
                        value = data_0836D634[height - (y + 1)][x];
                    if (value >= 0) {
                        s32 result = tile + value;

                        if (y > 3)
                            result += 0x800;
                        tiles[offset + last - x] = result;
                    } else if (value == -1) {
                        tiles[offset + last - x] = fill;
                    }
                }
                offset += stride;
            }
        }
    }
}
