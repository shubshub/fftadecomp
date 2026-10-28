#include "ffta.h"

extern u32 func_080C92F0(void *unit, u32 selector);
extern u8 func_080CD95C(const void *unit);
extern s32 func_080CA4F0(const void *unit, u8 selector);

/* Complete [0x0812C7B8, 0x0812C7F2): 58 bytes, 26 instructions. */
s32 func_0812C7B8(void *unit)
{
    s32 value = func_080C92F0(unit, 0x20);

    if (!func_080CD95C(unit))
        value += func_080CA4F0(unit, 15);
    if (value < 0)
        return 0;
    if (value > 100)
        return 100;
    return value;
}
