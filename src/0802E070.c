#include "ffta.h"

extern u8 *data_0200F444;

/* 0x0802E070..0x0802E08C: 28 bytes. */
void func_0802E070(void)
{
    u8 value = data_0200F444[0x465];

    data_0200F444[0x466] = value;
}
