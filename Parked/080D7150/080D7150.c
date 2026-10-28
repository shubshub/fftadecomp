#include "ffta.h"

void func_080D7150(const u8 *input, u16 length, u8 *output, u8 palette)
{
    u16 i;

    palette <<= 4;
    for (i = 0; i < length; i++) {
        u32 packed = input[i];
        u16 j;

        for (j = 0; j < 2; j++) {
            u8 value = packed & 0xF;

            *output = value;
            if (value)
                *output |= palette;
            output++;
            packed >>= 4;
        }
    }
}
