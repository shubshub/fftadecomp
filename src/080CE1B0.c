#include "ffta.h"

void func_080CE1B0(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 8;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
