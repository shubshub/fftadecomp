#include "ffta.h"

typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outerWidth;
    u8 unknown_13;
    u16 value;
    u8 stride;
    u8 mode;
    u16 first;
    u16 last;
    u8 flags;
    u8 unknown_1D[2];
    u8 alignment;
    u16 width;
    u16 height;
    s16 expectedWidth;
    s16 expectedHeight;
} TileRegion;

extern void func_08016FE4(TileRegion *region);
extern void func_08016B50(TileRegion *region);
extern u16 func_080161A0(u8 x, u8 y, u8 stride);
extern void func_08016A98(u16 *destination, u8 width, u8 height,
                          u16 value, u8 stride);
extern void func_08016268(u16 *primary, const u16 *secondary,
                          u8 width, u8 height, u16 value, u8 stride,
                          u16 first, u16 last, u8 mode);
extern void func_08016E88(TileRegion *region, u16 position, u8 width);

/* Target: complete [0x08017180, 0x080172F0), 368 bytes. */
u8 func_08017180(TileRegion *region)
{
    u32 y;
    u16 width;
    u16 height;
    u16 position;
    u8 complete;

    if (!(region->flags & 4))
        func_08016FE4(region);
    func_08016B50(region);

    y = region->y;
    width = region->width;
    height = region->height;
    position = func_080161A0(region->x, y, region->stride);
    if (region->alignment & 1)
        position += (region->outerWidth - width) >> 1;
    else if (region->alignment & 2)
        position += region->outerWidth - width;

    if ((region->flags & 4) && width > 2 && height > 2)
    {
        if (region->flags & 8)
        {
            u16 offset = func_080161A0(0, y - 1, region->stride);
            func_08016A98(region->primary + offset, 30,
                          region->expectedHeight + 2, 0, region->stride);
            func_08016A98(region->secondary + offset, 30,
                          region->expectedHeight + 2, 0, region->stride);
        }
        else
            func_08016A98(region->primary + position, width, height,
                          0, region->stride);
    }

    if (region->secondary)
        func_08016268(region->primary + position,
                      region->secondary + position, width, height,
                      region->value, region->stride,
                      region->first, region->last, region->mode);
    else
        func_08016268(region->primary + position, 0, width, height,
                      region->value, region->stride,
                      region->first, region->last, region->mode);

    func_08016E88(region, position, width);
    complete = 0;
    if (width == region->expectedWidth && height == region->expectedHeight)
        complete = 1;
    return complete;
}
