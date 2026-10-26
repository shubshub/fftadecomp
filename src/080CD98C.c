#include "ffta.h"

/* Complete [0x080CD98C, 0x080CD9A4): 24 bytes, 12 instructions. */
u8 func_080CD98C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE9;
    u8 mask = 4;

    if (!(*flags & mask))
        return 0;
    return 1;
}
