#include "ffta.h"

void func_080CE0B8(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEB;
    u8 mask = 4;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
