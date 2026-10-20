#include "ffta.h"

void func_080CDE38(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xE9;
    u8 mask = 2;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
