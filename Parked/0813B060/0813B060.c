#include "ffta.h"

/* Target: complete [0x0813B060, 0x0813B0A8), 72 bytes, 33 instructions.
 * Output is a halfword count followed by byte-indexed storage; its complete
 * allocation extent is unknown. */
typedef struct {
    u16 count;
    u8 indices[0];
} Output0813B060;

extern const u16 data_030027B0[];

u8 func_0813B060(u8 selector, Output0813B060 *output)
{
    u16 count = 0;
    u16 index;

    for (index = 0; index < 16; index++) {
        u32 entry = data_030027B0[index];

        if ((entry >> 8) == selector) {
            output->indices[entry & 0xff] = index;
            count++;
        }
    }
    output->count = count;
    return count;
}
