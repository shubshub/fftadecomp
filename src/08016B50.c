#include "ffta.h"

typedef struct TileRegion {
    u8 unknown_00[0x20];
    u16 width;
    u16 height;
    s16 expected_width;
    s16 expected_height;
    u16 width_step;
    u16 height_step;
} TileRegion;

/* 08016B50..08016BBA: 106 bytes, 53 instructions. */
void func_08016B50(TileRegion *region)
{
    if ((s16)region->height < region->expected_height) {
        region->height += region->height_step;
        if ((s16)region->height > region->expected_height)
            region->height = region->expected_height;
    } else {
        region->height -= region->height_step;
        if ((s16)region->height < region->expected_height)
            region->height = region->expected_height;
    }

    if ((s16)region->width < region->expected_width) {
        region->width += region->width_step;
        if ((s16)region->width > region->expected_width)
            region->width = region->expected_width;
    } else {
        region->width -= region->width_step;
        if ((s16)region->width < region->expected_width)
            region->width = region->expected_width;
    }
}
