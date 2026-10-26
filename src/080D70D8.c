#include "ffta.h"

/* 0x080D70D8..0x080D7150: 120 bytes, 60 instructions. */
void func_080D70D8(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i += 3) {
        const u8 *input = source + i;
        u32 bits = input[0] | (input[1] << 8) | (input[2] << 16);
        u16 pixel;

        for (pixel = 0; pixel < 8; pixel++) {
            *destination = bits & 7;
            if (bits & 7) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 3;
        }
    }
}
