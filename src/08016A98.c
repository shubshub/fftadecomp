#include "ffta.h"

extern void func_0814186C(const void *source, void *destination, u32 control);

/* 08016A98..08016AEC, 84 bytes. Clear a rectangle of tilemap entries. */
void func_08016A98(u16 *destination, u8 width, u8 height,
                   u16 unused_value, u8 stride)
{
    u16 *row = destination;
    s32 remaining = height;

    while (remaining != 0) {
        s32 byte_count = width * 2;
        u16 zero;
        u16 *source = &zero;

        *source = 0;
        func_0814186C(source, row, 0x01000000 | ((byte_count / 2) & 0x1FFFFF));
        row += stride;
        remaining--;
    }
}
