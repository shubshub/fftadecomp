#include "ffta.h"

s32 func_080CA624(const void *object, u8 enabled);

s32 func_080CA520(const void *object)
{
    s32 value = func_080CA624(object, 1);

    if (value > 999)
        value = 999;
    return value;
}
