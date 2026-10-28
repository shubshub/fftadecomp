#include "ffta.h"

void func_0802BD44(u32 *destination, const u32 *source)
{
    const u32 *input = source;
    u32 *output = destination;
    s32 row;

    for (row = 0; row < 8; input++, output++, row++) {
        u32 value = *input;
        u32 mask = 0;
        u32 nibble = 0xF;
        u32 previous = *output;
        s32 column;

        for (column = 0; column < 8; column++, nibble <<= 4) {
            if (value & nibble)
                mask |= nibble;
        }

        *output = (previous & ~mask) | value;
    }
}
