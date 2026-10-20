#include "ffta.h"

void func_080CDF78(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEC;
    u8 mask = 2;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
