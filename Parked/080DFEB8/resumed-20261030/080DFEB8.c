#include "ffta.h"

extern u32 func_08005BB0(const void *object);

/* 0x080DFEB8..0x080DFECC:
 * 00 B5 25 F7 79 FE 00 28 01 D1 00 20 00 E0 01 20 02 BC 08 47. */
u8 func_080DFEB8(const void *object)
{
    if (func_08005BB0(object) == 0)
        return 0;
    return 1;
}
