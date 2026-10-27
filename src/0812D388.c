#include "ffta.h"

extern s32 func_0812C8DC(const void *source, const void *target,
                        u32 mode, u32 flags);

s32 func_0812D388(const void *source, const void *target)
{
    return func_0812C8DC(source, target, 2, 0);
}
