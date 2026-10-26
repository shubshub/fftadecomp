#include "ffta.h"

/* Complete [0x080CDBFC, 0x080CDC14): 24 bytes, 12 instructions. */
u8 func_080CDBFC(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEC;
    u8 mask = 0x10;

    if (!(*flags & mask))
        return 0;
    return 1;
}
