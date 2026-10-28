#include "ffta.h"

/* Target: [0x0812B570, 0x0812B59A), 42 bytes, 21 instructions. */
u8 func_0812B570(const u8 *text)
{
    u8 index;

    for (index = 0; index < 9; index++) {
        const u8 *pair = text + index * 2;

        if (pair[0] != 0x40 || pair[1] != 0x73)
            return 0;
    }
    return 1;
}
