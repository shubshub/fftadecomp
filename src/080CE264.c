#include "ffta.h"

void func_080CE264(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEC;
    u8 mask = 0x80;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
