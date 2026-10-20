#include "ffta.h"

void func_080CD884(void *data, u16 index, u8 enabled)
{
    u32 offset = 0xE8 + (index >> 3);
    u8 *flags = (u8 *)data + offset;
    u8 mask = 1 << (index & 7);

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
