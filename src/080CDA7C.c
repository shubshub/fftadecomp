#include "ffta.h"

/* Complete [0x080CDA7C, 0x080CDA94): 24 bytes, 12 instructions. */
u8 func_080CDA7C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEA;
    u8 mask = 4;

    if (!(*flags & mask))
        return 0;
    return 1;
}
