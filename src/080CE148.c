#include "ffta.h"

void func_080CE148(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEB;
    u8 mask = 0x40;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
