#include "ffta.h"

void func_08021C08(u32 *flags, u8 enabled)
{
    if (enabled)
        *flags |= 0x40000;
    else
        *flags &= ~0x40000;
}
