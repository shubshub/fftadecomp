#include "ffta.h"

/* 0x080D7080..0x080D70D8: 88 bytes, 44 instructions. */
void func_080D7080(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 bits = source[i];
        u16 pixel;

        for (pixel = 0; pixel < 4; pixel++) {
            *destination = bits & 3;
            if (*destination) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 2;
        }
    }
}
