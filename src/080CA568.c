#include "ffta.h"

s32 func_080CA6FC(const void *object, u8 enabled);

s32 func_080CA568(const void *object)
{
    s32 value = func_080CA6FC(object, 1);

    if (value > 999)
        return 999;
    return value;
}
