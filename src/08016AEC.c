#include "ffta.h"

typedef struct Rectangle {
    u8 left;
    u8 top;
    u8 width;
    u8 height;
} Rectangle;

extern u16 func_080161A0(u8 x, u8 y, u8 stride);
extern void func_0814186C(const void *source, void *destination, u32 count);

/* 08016AEC..08016B4E: 98 bytes, 47 instructions. */
void func_08016AEC(u16 *destination, u8 destination_stride,
                   const u16 *source, Rectangle area, u8 source_stride)
{
    u16 *output = destination;
    const u16 *cursor;
    s32 remaining;

    cursor = source + func_080161A0(area.left, area.top, source_stride);
    remaining = area.height;
    while (remaining != 0) {
        func_0814186C(cursor, output, area.width);
        cursor += source_stride;
        output += destination_stride;
        remaining--;
    }
}
