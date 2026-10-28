#include "ffta.h"

/* 0x080D7A9C..0x080D7AB0: 20 bytes. */
extern u32 func_08005BB0(u32 handle);

u8 func_080D7A9C(u32 handle)
{
    if (func_08005BB0(handle) != 0)
        return 1;
    return 0;
}
