#include "ffta.h"

void func_080CE100(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEB;
    u8 mask = 0x10;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
