#include "ffta.h"

/* 0x0803A7C0..0x0803A7EC: 44 bytes. */
u8 func_0803A7C0(u8 value, const u8 *values, s32 length)
{
    u8 count = 0;
    s32 i;

    for (i = 0; i < length; i++) {
        if (value == values[i])
            count++;
    }
    return count;
}
