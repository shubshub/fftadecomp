#include "ffta.h"

u32 func_080C8570(u8 first, u8 second, u8 selector);
s32 func_080C7EA4(const void *object, u32 selector);
s32 func_080C9134(u8 selector);

s32 func_080C9428(const void *data)
{
    const u8 *object = data;
    u8 flags = func_080C8570(object[5], object[7], 0x28);
    s32 result;

    if (flags & 1)
        result = func_080C9134(func_080C7EA4(object, 4));
    else
        result = -1;
    return result;
}
