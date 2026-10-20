#include "ffta.h"

u8 func_080CD8E4(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE8;
    u8 mask = 0x08;

    if (!(*flags & mask))
        return 0;
    return 1;
}
