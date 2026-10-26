#include "ffta.h"

void func_080D6FBC(const u8 *input, u16 length, u8 *output)
{
    u16 i;

    for (i = 0; i < length; i += 3) {
        const u8 *chunk = input + i;
        u32 packed = chunk[0] | (chunk[1] << 8) | (chunk[2] << 16);
        u16 j;

        *output = 0;
        for (j = 0; j < 8; j++) {
            u8 value = packed & 7;

            if (j & 1) {
                *output |= value << 4;
                output++;
                *output = 0;
            } else {
                *output |= value;
            }
            packed >>= 3;
        }
    }
}
