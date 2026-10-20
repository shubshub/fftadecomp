#include "ffta.h"

s32 func_080CA6B4(const void *object, u8 enabled);

s32 func_080CA550(const void *object)
{
    s32 value = func_080CA6B4(object, 1);

    if (value > 999)
        value = 999;
    return value;
}
