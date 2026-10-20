#include "ffta.h"

void func_080CE380(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xED;
    u8 mask = 0x80;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
