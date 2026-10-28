#include "ffta.h"

/* 0x08017618..0x08017732: 282 bytes, 141 instructions. */
typedef struct {
    u8 unknown_00[12];
    u16 *tiles;
    u16 flags;
    u8 unknown_12[3];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[4];
    u16 base_tile;
    u8 unknown_1E;
    u8 palette;
} TileRegion;

void func_08017618(TileRegion *region, u8 width)
{
    u16 *row = region->tiles;
    u16 tile = (region->palette << 12) + region->base_tile;
    s32 start = (u16)(region->flags & 2) ? 2 : 0;
    s32 end = width;
    s32 rows;

    if (region->flags & 4) {
        end -= 2;
    }
    for (rows = region->rows; rows != 0; rows--) {
        s32 column;
        if (start) {
            row[0] = tile++;
            row[1] = tile++;
            row[region->stride] = tile++;
            row[region->stride + 1] = tile++;
        }
        for (column = start; column < end; column++) {
            u16 *destination = row + column;
            destination[0] = tile++;
            destination[region->stride] = tile++;
        }
        if (end != width) {
            u16 *edge = row;
            edge += end;
            edge[0] = tile++;
            edge[1] = tile++;
            edge[region->stride] = tile++;
            edge[region->stride + 1] = tile++;
        }
        row += region->stride * 2;
    }
}
