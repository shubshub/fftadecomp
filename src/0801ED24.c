#include "ffta.h"

/* 0x0801ED24..0x0801EFAE: 650 bytes, 315 instructions. */
extern u8 *func_0801AD1C(u8 selector);

const u8 *func_0801ED24(const u8 *source, const void *table, u8 flags,
                       u16 *screen0, u16 *screen1, u16 origin_x,
                       u16 origin_y, s16 remaining)
{
    u16 *destination;
    const u16 *short_table;
    u16 screen_x;
    u16 screen_y;
    u8 short_entries;
    u8 wide_indices;
    u8 clipped;
    u8 *base;

    destination = 0;
    clipped = 0;
    base = func_0801AD1C(0);
    short_table = table;
    short_entries = flags & 1;
    if (flags & 2)
        wide_indices = 1;
    else
        wide_indices = 0;

    if (flags & 4)
        remaining = 0;
    if (screen0 != 0 || screen1 != 0)
        clipped = 1;

    screen_x = 0;
    screen_y = 0;
    for (;;) {
        u16 offset = source[0] | (source[1] << 8);
        s16 count;
        s16 i;

        source += 2;
        if (clipped) {
            screen_x = (offset >> 1) & 0x3f;
            screen_y = (offset >> 1) >> 6;
            if (offset >= 0x2000)
                screen_y -= 0x40;
        }

        if (table != 0) {
            count = *source++;
            if (clipped) {
                if (screen_y >= origin_y + 32) {
                    source += count;
                    if ((source[0] | source[1]) == 0)
                        goto end;
                    continue;
                }
            } else {
                destination = (u16 *)(base + offset);
            }

            for (i = 0; i < count; i++) {
                u32 index;
                u32 pair;

                if (wide_indices) {
                    index = source[0] | (source[1] << 8);
                    source += 2;
                } else {
                    index = *source++;
                }

                if (short_entries) {
                    pair = short_table[index];
                    if (pair & 0x80008000) {
                        pair |= short_table[index + 1] << 16;
                        pair &= 0x7fff7fff;
                    } else {
                        pair |= (pair + 1) << 16;
                    }
                } else {
                    pair = ((const u32 *)table)[index];
                }

                if (clipped) {
                    s16 x;
                    s16 y;
                    u16 position;

                    destination = 0;
                    x = screen_x + i * 2;
                    y = screen_y;
                    if (x > 63) {
                        x -= 64;
                        y++;
                    }
                    x -= origin_x;
                    y -= origin_y;
                    position = x + (y << 5);
                    if (offset < 0x2000) {
                        if (screen0 != 0)
                            destination = screen0 + position;
                    } else {
                        if (screen1 != 0)
                            destination = screen1 + position;
                    }

                    if (destination != 0) {
                        if (x >= 0 && x < 32 && y >= 0 && y < 32)
                            *destination = pair;
                        destination++;
                        if (x + 1 >= 0 && x + 1 < 32 && y >= 0 && y < 32)
                            *destination = pair >> 16;
                    }
                } else {
                    *(u32 *)destination = pair;
                    destination += 2;
                }
            }

            if ((source[0] | source[1]) == 0)
                goto end;
            if (remaining != 0) {
                remaining -= count * 4;
                if (remaining <= 0)
                    return source;
            }
        } else {
            count = source[0] | (source[1] << 8);
            count >>= 2;
            source += 2;
            for (i = 0; i < count; i++) {
                u32 pair = source[0] | (source[1] << 8) |
                           (source[2] << 16) | (source[3] << 24);
                source += 4;
                *(u32 *)destination = pair;
                destination += 2;
            }
            if ((source[0] | source[1]) == 0)
                goto end;
            if (remaining != 0) {
                remaining -= count * 4;
                if (remaining <= 0)
                    return source;
            }
        }
    }
end:
    return 0;
}
