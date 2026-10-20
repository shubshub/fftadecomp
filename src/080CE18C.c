#include "ffta.h"

void func_080CE18C(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEC;
    u8 mask = 1;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
