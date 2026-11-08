#include "ffta.h"

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080CCD50(u16 entry, u8 selector);

static inline u16 check(u16 unit)
{
    s16 value = func_080CA7A4(unit, 3);

    if ((u16)(value - 13) <= 1)
        return 0x1C0;
    if (value == 19)
        return 0x1C0;
    return 0x180;
}

/* Complete target: [0x080B42E4, 0x080B43EA), 262 bytes. */
u16 func_080B42E4(u16 first, u16 second)
{
    u16 value4;
    u16 flags;

    if (first == 0)
        return check(second);

    value4 = func_080CCD50(first, 4);
    flags = 0;
    if (value4 & 0x80)
        return check(second);

    if (value4 & 0x40)
        flags = 1;
    flags |= 0x80;
    if (func_080CCD50(first, 11) == 0)
        flags |= 0x100;

    switch ((u16)func_080CCD50(first, 6)) {
    case 2:
        return 4;
    case 3:
        if ((flags & 0xF) == 1)
            return flags;
        return flags | 0x42;
    case 4:
        return flags | 0x20;
    case 5:
    case 6:
        return flags | 0x30;
    case 7:
        return flags | 0x10;
    default:
        return flags | 0x40;
    }
}
