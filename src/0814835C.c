#include "ffta.h"

/* 0x0814835C..0x08148384: 40 bytes. */
void func_0814835C(u16 *destination, u16 value, u16 count)
{
    u16 i;

    for (i = 0; i < count; ++i)
        destination[i] = value;
}
