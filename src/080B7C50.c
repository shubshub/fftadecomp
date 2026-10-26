#include "ffta.h"

/* 0x080B7C50: 68 bytes. */
u32 func_080C92F0(void *object, u32 selector);
u16 func_080B7C2C(u16 first, u16 second, u8 mode);

u16 func_080B7C50(void *object, u16 first, u16 second, u8 mode)
{
    if (object != 0 && (func_080C92F0(object, 0x28) & 4)) {
        if (mode == 0)
            return 0x1C0;
        else
            return 0x1C2;
    }
    return func_080B7C2C(first, second, mode);
}
