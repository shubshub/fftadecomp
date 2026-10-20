#include "ffta.h"

void func_080CDFC0(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 4;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
