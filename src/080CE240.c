#include "ffta.h"

void func_080CE240(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEC;
    u8 mask = 0x40;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
