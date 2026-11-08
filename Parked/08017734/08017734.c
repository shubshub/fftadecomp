#include "ffta.h"

/* 0x08017734..0x0801784C: 280 bytes.
 *
 * NOT YET MATCHING (128 vs 128 instructions, bl counted once, 40 differ):
 *  - the target keeps the region pointer in r5 and the row source in r6;
 *    this build swaps them (and the 0xFFF / 0xD000 temporaries with them);
 *  - the target loads sl = 0xFFF before computing (width - 2) * 2 into
 *    [sp, #0xc]; here the order is reversed.  In the target the shift-left
 *    looks loop-hoisted while the asrs #1 stays in the loop; writing the
 *    expression inside the loop lets combine fold it to `width - 2`.
 */
typedef struct {
    u8 (*palette_of)(void *context, u32 index);
    void *context;
    u16 *destination;
    u16 *tiles;
    u16 flags;
    u8 width;
    u8 unknown_13[2];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u8 unknown_18[6];
    u8 destination_stride;
} TileRegion;

extern u16 func_08017B50(TileRegion *region);
extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08017734(TileRegion *region, u16 start)
{
    u16 *source;
    u32 stride;
    s32 width;
    u16 index = start;
    u16 row = start;
    s32 count = (u16)(func_08017B50(region) * 2);
    u16 *destination;
    s32 size;

    stride = region->stride;
    width = region->width;
    destination = region->destination;
    if (count == 0)
        return;
    size = (width - 2) * 2;
    while (count != 0) {
        row = func_08142950(row, region->rows * 2);
        source = region->tiles + row * stride;
        if (region->palette_of) {
            u32 palette = region->palette_of(region->context, index++ >> 1) << 12;
            destination[0] = (source[0] & 0xFFF) | palette;
            destination[1] = (source[1] & 0xFFF) | palette;
            func_0814186C(source + 2, destination + 2, (size >> 1) & 0x1FFFFF);
        } else {
            func_0814186C(source, destination, width & 0x1FFFFF);
        }
        if (region->flags & 4) {
            destination[stride - 2] = (source[stride - 2] & 0xFFF) | 0xD000;
            destination[stride - 1] = (source[stride - 1] & 0xFFF) | 0xD000;
        }
        destination += region->destination_stride;
        count--;
        row++;
    }
}
