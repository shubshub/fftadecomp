#include "ffta.h"

/* Complete [0x080CDB0C, 0x080CDB24): 24 bytes, 12 instructions. */
u8 func_080CDB0C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEB;
    u8 mask = 2;

    if (!(*flags & mask))
        return 0;
    return 1;
}
