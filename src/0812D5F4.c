#include "ffta.h"

extern s32 func_080CA3EC(const void *object);
extern u8 func_0812D474(const void *source, const void *target, u32 action);
extern s32 func_0812C8DC(const void *source, const void *target,
                         u32 mode, u32 option);
extern u8 func_080CD50C(const void *object);
extern u8 func_0812D5A0(const void *object);

/* 0x0812D5F4..0x0812D65E: 106 bytes, 47 instructions. */
s32 func_0812D5F4(const void *source, const void *target, u32 action, s32 mode)
{
    s32 result;

    if ((u32)func_080CA3EC(target) / 10 == 0)
        return 0;
    if (!func_0812D474(source, target, action))
        return 0;
    result = func_0812C8DC(source, target, 2, 0);
    if (func_080CD50C(target) == 9)
        return 0;
    if (result < 100) {
        if (mode == 15)
            result >>= 2;
        if (func_0812D5A0(source))
            result += 20;
    }
    return result;
}
