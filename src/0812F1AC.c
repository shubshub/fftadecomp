#include "ffta.h"

/* 0x0812F1AC..0x0812F1CA: 30 bytes, 15 instructions. */
u8 func_0812F1AC(u16 value)
{
    s32 identifier = value;
    s32 minimum = 312;
    s32 maximum = 316;

    if (identifier <= maximum) {
        if (identifier >= minimum)
            return 1;
    }
    return 0;
}
