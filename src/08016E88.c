#include "ffta.h"

/* Target: complete [0x08016E88, 0x08016FE4), 348 bytes. */
typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[12];
    u16 flags;
    u8 stride;
    u8 palette;
    u8 unknown_18[5];
    u8 first;
    u8 second;
} TileRegion;

extern u32 func_080185B8(u8 index);

void func_08016E88(TileRegion *region, u16 position, u8 width)
{
    s32 first_length = 0;
    s32 i;

    if (region->flags & 0x1420)
        return;

    if (region->first) {
        u8 start;
        u8 end;

        first_length = func_080185B8(region->first & 0x7f);
        if (region->first & 0x80) {
            u8 second_length = func_080185B8(region->second & 0x7f);
            start = width - second_length - first_length - 2;
            end = width - second_length - 2;
            first_length += second_length;
        } else {
            start = 1;
            end = first_length + 1;
        }
        if (width > first_length + 1) {
            u16 *tiles;
            u16 tile;

            if (region->flags & 0x800) {
                tiles = region->secondary + position;
                tile = (region->palette << 12) + 0x4a;
            } else {
                tiles = region->primary + position + region->stride;
                tile = (region->palette << 12) + 0x3e;
            }
            for (i = start; i < end; ++i)
                tiles[i] = tile++;
        }
    }

    if (region->second) {
        u8 start;
        u8 end;
        s32 second_length = func_080185B8(region->second & 0x7f);

        if (region->second & 0x80) {
            first_length = 0;
            start = 1;
            end = second_length + 1;
        } else {
            start = width - second_length - 1;
            end = width - 1;
        }
        if (width > first_length + second_length + 1) {
            u16 *tiles;
            u16 tile;

            if (region->flags & 0x800) {
                tiles = region->secondary + position;
                tile = (region->palette << 12) + 0x4a;
            } else {
                tiles = region->primary + position + region->stride;
                tile = (region->palette << 12) + 0x44;
            }
            for (i = start; i < end; ++i)
                tiles[i] = tile++;
        }
    }
}
