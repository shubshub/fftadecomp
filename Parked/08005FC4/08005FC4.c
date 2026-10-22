#include "ffta.h"

s32 func_0814187C(s32 denominator, s32 numerator);

static inline u16 read_descriptor_flags(const u8 *descriptor)
{
    return descriptor[6] | (descriptor[7] << 8);
}

void func_08005FC4(const void *source_descriptor, u8 palette, u16 tile_offset,
                   u16 transparent, u16 fill, const void *destination_descriptor)
{
    const u8 *source = source_descriptor;
    const u8 *destination = destination_descriptor;
    u16 flags = read_descriptor_flags(source);
    u32 horizontal_flip = flags & 1;
    u32 vertical_flip = (flags >> 1) & 1;
    u16 row;
    u16 column;
    u16 source_row;
    u16 source_column;
    u16 value;

    for (row = 0; row < destination[5]; row++) {
        if (row >= source[5] &&
            (read_descriptor_flags(source) & 8)) {
            source_row = func_0814187C(source[5], row);
        } else {
            source_row = row;
        }
        if (vertical_flip && source_row < source[5])
            source_row = source[5] - (source_row + 1);

        for (column = 0; column < destination[4]; column++) {
            if (column >= source[4] &&
                (read_descriptor_flags(source) & 4)) {
                source_column = func_0814187C(source[4], column);
            } else {
                source_column = column;
            }
            if (horizontal_flip && source_column < source[4])
                source_column = source[4] - (source_column + 1);

            if (source_row < source[5] && source_column < source[4]) {
                if (read_descriptor_flags(source) & 0x8000) {
                    const u8 *data = (const u8 *)((u32)source[0] |
                                                ((u32)source[1] << 8) |
                                                ((u32)source[2] << 16) |
                                                ((u32)source[3] << 24));

                    value = data[source_row * source[4] + source_column];
                    if (value == transparent)
                        value = fill;
                } else {
                    const u16 *data = (const u16 *)((u32)source[0] |
                                                  ((u32)source[1] << 8) |
                                                  ((u32)source[2] << 16) |
                                                  ((u32)source[3] << 24));

                    value = data[source_row * source[4] + source_column];
                    if ((value & 0x3FF) == transparent) {
                        value = fill;
                    } else {
                        value += tile_offset;
                        value += palette << 12;
                        if (horizontal_flip)
                            value ^= 0x400;
                        if (vertical_flip)
                            value ^= 0x800;
                    }
                }
            } else {
                value = fill;
            }

            if (read_descriptor_flags(destination) & 0x8000) {
                u8 *data = (u8 *)((u32)destination[0] |
                                  ((u32)destination[1] << 8) |
                                  ((u32)destination[2] << 16) |
                                  ((u32)destination[3] << 24));

                data[row * destination[4] + column] = value;
            } else {
                u16 *data = (u16 *)((u32)destination[0] |
                                    ((u32)destination[1] << 8) |
                                    ((u32)destination[2] << 16) |
                                    ((u32)destination[3] << 24));

                data[row * destination[4] + column] = value;
            }
            if (read_descriptor_flags(source) & 0x10)
                horizontal_flip ^= 1;
        }
        if (read_descriptor_flags(source) & 0x20)
            vertical_flip ^= 1;
    }
}
