#include "ffta.h"

// 0x080D7150..0x080D71A8: 88 bytes, 44 instructions.
void func_080D7150(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 bits = source[i];
        u16 pixel;

        for (pixel = 0; pixel < 2; pixel++) {
            *destination = bits & 0xF;
            if (*destination) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 4;
        }
    }
}
