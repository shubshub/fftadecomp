#include "ffta.h"

s32 func_080CA66C(const void *object, u8 enabled);

s32 func_080CA538(const void *object)
{
    s32 value = func_080CA66C(object, 1);

    if (value > 999)
        value = 999;
    return value;
}
