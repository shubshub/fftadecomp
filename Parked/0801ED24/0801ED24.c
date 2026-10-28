#include "ffta.h"

extern u8 *func_0801AD1C(void);

/* Complete target: [0x0801ED24, 0x0801EFAE), 650 bytes. */
const u8 *func_0801ED24(const u8 *source, const void *table, u8 flags,
                       u16 *screen0, u16 *screen1, u16 origin_x,
                       u16 origin_y, u16 remaining)
{
    u32 *destination = 0;
    u8 clipped = 0;
    u8 *base = func_0801AD1C();
    const u16 *short_table = table;
    u8 short_entries = flags & 1;
    u8 wide_indices = flags & 2;

    wide_indices = wide_indices != 0;

    if (flags & 4)
        remaining = 0;
    if (screen0 != 0 || screen1 != 0)
        clipped = 1;

    for (;;) {
        u16 screen_x = 0;
        u16 screen_y = 0;
        u16 offset = source[0] | (source[1] << 8);
        s16 count;
        s16 i;

        source += 2;
        if (clipped) {
            u16 tile_position = offset >> 1;
            screen_x = tile_position & 0x3f;
            screen_y = tile_position >> 6;
            if (offset > 0x1fff)
                screen_y -= 0x40;
        }

        if (table != 0) {
            count = *source++;
            if (clipped) {
                if (screen_y >= origin_y + 32) {
                    source += count;
                    if ((source[0] | source[1]) == 0)
                        return 0;
                    continue;
                }
            } else {
                destination = (u32 *)(base + offset);
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
                    const u16 *entry = short_table + index;
                    pair = entry[0];
                    if (pair & 0x80008000) {
                        pair |= entry[1] << 16;
                        pair &= 0x7fff7fff;
                    } else {
                        pair |= (pair + 1) << 16;
                    }
                } else {
                    pair = ((const u32 *)table)[index];
                }

                if (clipped) {
                    u16 x;
                    u16 y;
                    s32 position;
                    u16 *screen;

                    destination = 0;
                    x = screen_x + i * 2;
                    y = screen_y;
                    if ((s16)x > 63) {
                        x -= 64;
                        y++;
                    }
                    x -= origin_x;
                    y -= origin_y;
                    position = (s16)x + ((s16)y << 5);
                    if (offset <= 0x1fff)
                        screen = screen0;
                    else
                        screen = screen1;
                    if (screen != 0)
                        destination = (u32 *)(screen + (u16)position);

                    if (destination != 0) {
                        if (x <= 31 && (s16)y >= 0 && (s16)y <= 31)
                            ((u16 *)destination)[0] = pair;
                        destination = (u32 *)((u16 *)destination + 1);
                        if ((u16)(x + 1) <= 31 && (s16)y >= 0 && (s16)y <= 31)
                            *(u16 *)destination = pair >> 16;
                    }
                } else {
                    *destination++ = pair;
                }
            }

            if ((source[0] | source[1]) == 0)
                return 0;
            {
                s32 budget = (s16)remaining;
                if (budget != 0) {
                    remaining = budget - (s16)count * 4;
                    if ((s16)remaining <= 0)
                        return source;
                }
            }
        } else {
            count = (s16)(source[0] | (source[1] << 8)) >> 2;
            source += 2;
            for (i = 0; i < count; i++) {
                u32 pair = source[0] | (source[1] << 8) |
                           (source[2] << 16) | (source[3] << 24);
                source += 4;
                *destination++ = pair;
            }
            if ((source[0] | source[1]) == 0)
                return 0;
            {
                s32 budget = (s16)remaining;
                if (budget != 0) {
                    remaining = budget - (s16)count * 4;
                    if ((s16)remaining <= 0)
                        return source;
                }
            }
        }
    }
}
