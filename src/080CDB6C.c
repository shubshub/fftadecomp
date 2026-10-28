#include "ffta.h"

/* Complete [0x080CDB6C, 0x080CDB84): 24 bytes, 12 instructions. */
u8 func_080CDB6C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEB;
    u8 mask = 0x20;

    if (!(*flags & mask))
        return 0;
    return 1;
}
