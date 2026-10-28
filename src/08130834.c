#include "ffta.h"

extern u8 func_080C95A8(u16 index);
extern u8 func_080C8240(void *unit);
extern u8 func_080C82B8(const void *unit);

/* Complete [0x08130834, 0x08130868): 52 bytes, 23 instructions. */
u8 func_08130834(void *unit)
{
    if (!func_080C95A8(13))
        return 0;
    if (!func_080C8240(unit))
        return 0;
    if (!func_080C82B8(unit))
        return 0;
    return 1;
}
