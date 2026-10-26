#include "ffta.h"

/* 0x080D71A8..0x080D721E: 118 bytes, 59 instructions. */
void func_080D71A8(const u8 *source, u16 count, u8 *destination, u16 offset)
{
    u16 i;

    for (i = 0; i < count; i += 3) {
        const u8 *input = source + i;
        u32 bits = input[0] | (input[1] << 8) | (input[2] << 16);
        u16 pixel;

        for (pixel = 0; pixel < 4; pixel++) {
            *destination = bits & 0x3F;
            if (bits & 0x3F) {
                *destination += offset;
            }
            destination++;
            bits >>= 6;
        }
    }
}
