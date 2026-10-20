#include "ffta.h"

s32 func_080CA6B4(const void *object, u8 enabled);
s32 func_080CA6FC(const void *object, u8 enabled);

s32 func_080CA4B0(const void *object, u8 flags)
{
    s32 value;

    if (flags & 1)
        value = func_080CA6B4(object, 1);
    else if (flags & 2)
        value = func_080CA6FC(object, 1);
    else
        value = 0;
    if (value > 999)
        return 999;
    return value;
}
