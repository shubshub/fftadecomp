#include "ffta.h"

extern u32 func_080C92F0(const void *object, u32 selector);
extern u8 func_080CDA1C(const void *object);

/* 0x0812E0FC..0x0812E130: 52 bytes, 23 instructions. */
s32 func_0812E0FC(const void *object)
{
    s32 result = func_080C92F0(object, 0x20) / 10;

    if (func_080CDA1C(object))
        result += 30;
    if (result < 0)
        result = 0;
    if (result > 100)
        result = 100;
    return result;
}
