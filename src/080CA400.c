#include "ffta.h"

s32 func_080CA624(const void *object, u8 enabled);
s32 func_080CA66C(const void *object, u8 enabled);

s32 func_080CA400(const void *object, u8 flags, u8 enabled)
{
    if (flags & 1)
        return func_080CA624(object, enabled);
    if (flags & 2)
        return func_080CA66C(object, enabled);
    return 0;
}
