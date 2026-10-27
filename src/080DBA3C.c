#include "ffta.h"

/* 0x080DBA3C..0x080DBA50: 20 bytes / 9 instructions. */
extern u32 func_08005BB0(const void *object);

u8 func_080DBA3C(const void *object)
{
    if (func_08005BB0(object) != 0)
        return 1;
    return 0;
}
