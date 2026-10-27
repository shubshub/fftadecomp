#include "ffta.h"

extern s32 func_080C7EA4(const void *object, u32 selector);
extern s32 func_0812F704(const void *object, u32 selector);
extern u32 func_08002804(void);

s16 func_081303FC(const void *object)
{
    u16 base = func_080C7EA4(object, 0x16);
    u16 bonus = func_0812F704(object, 1);
    u32 random = func_08002804();
    s32 center = ((s16)base + (s16)bonus) / 16 - 5;
    s16 result = center + (s16)random % 11;

    if (result <= 0)
        result = 1;
    return result;
}
