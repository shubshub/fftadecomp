#include "ffta.h"

/* 0x0812F874..0x0812F8A4: 48 bytes, 22 instructions. */
extern u8 func_080CD95C(const void *unit);
extern s32 func_080CA4F0(const void *unit, u8 selector);

s32 func_0812F874(const void *unit, s32 value, u8 mode)
{
    if (!func_080CD95C(unit)) {
        if (mode == 0)
            value += func_080CA4F0(unit, 11);
        else
            value += func_080CA4F0(unit, 13);
    }
    return value;
}
