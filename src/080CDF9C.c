#include "ffta.h"

void func_080CDF9C(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 0x02;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
