#include "ffta.h"

s32 func_080CA6B4(const void *object, u8 enabled);
s32 func_080CA6FC(const void *object, u8 enabled);

s32 func_080CA478(const void *object, u8 flags, u8 enabled)
{
    if (flags & 1)
        return func_080CA6B4(object, enabled);
    if (flags & 2)
        return func_080CA6FC(object, enabled);
    return 0;
}
