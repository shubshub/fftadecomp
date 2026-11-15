#include "ffta.h"

typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outerWidth;
    u8 outerHeight;
    u16 value;
    u8 stride;
} TileRegion;

extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                          u8 height, u8 stride, u16 tile, u8 palette);

/* Target: complete [0x08017380, 0x08017424), 164 bytes. */
void func_08017380(TileRegion *region, u16 tile, u8 palette)
{
    u8 x = region->x + 1;
    u8 y = region->y + 1;
    u8 width = region->outerWidth - 2;
    u8 height = (region->outerHeight - 2) / 2;

    if (region->value & 2) {
        x = region->x;
        width = region->outerWidth;
    }
    if (region->value & 4) {
        y = region->y;
        height = (region->outerHeight & 1) ? region->outerHeight + 1
                                           : region->outerHeight;
        height /= 2;
    }
    if (!(region->value & 0xC20)) {
        y++;
        height = (u8)(region->outerHeight - 3) / 2;
    }
    func_080157A8(region->primary, x, y, width, height, region->stride,
                  tile, palette);
}
