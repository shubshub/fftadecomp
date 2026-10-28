#include "ffta.h"

/* Complete [0x080CDC5C, 0x080CDC74): 24 bytes, 12 instructions. */
u8 func_080CDC5C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xED;
    u8 mask = 1;

    if (!(*flags & mask))
        return 0;
    return 1;
}
