#include "ffta.h"

s32 func_080CA624(const void *object, u8 enabled);
s32 func_080CA66C(const void *object, u8 enabled);

s32 func_080CA438(const void *object, u8 flags)
{
    s32 value;

    if (flags & 1)
        value = func_080CA624(object, 1);
    else if (flags & 2)
        value = func_080CA66C(object, 1);
    else
        value = 0;
    if (value > 999)
        return 999;
    return value;
}
