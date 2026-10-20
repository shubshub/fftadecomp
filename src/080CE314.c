#include "ffta.h"

void func_080CE314(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xED;
    u8 mask = 0x10;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
