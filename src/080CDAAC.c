#include "ffta.h"

u8 func_080CDAAC(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEA;
    u8 mask = 0x20;

    if (!(*flags & mask))
        return 0;
    return 1;
}
