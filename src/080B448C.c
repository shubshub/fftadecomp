#include "ffta.h"

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080CCD50(u16 entry, u8 selector);

/* Complete target: [0x080B448C, 0x080B44F8), 108 bytes, 50 instructions. */
u8 func_080B448C(u16 first, u16 second)
{
    u16 value4;
    s32 value;

    if (first == 0) {
        if (second == 0)
            value = 1;
        else
            value = func_080CA7A4(second, 5);
        return value;
    }
    value4 = func_080CCD50(first, 4);
    if (value4 & 0x80) {
        if (second == 0)
            value = 1;
        else
            value = func_080CA7A4(second, 5);
        return value;
    }
    if ((value4 & 0xC0) == 0)
        return value4;
    return func_080CCD50(first, 7) & 0x3F;
}
