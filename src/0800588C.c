#include "ffta.h"

/* 0x0800588C-0x080058A4: 24 bytes. */
u32 func_0800588C(const u8 *bytes)
{
    u32 value = (u32)bytes[0] << 24;

    value |= (u32)bytes[1] << 16;
    value |= (u32)bytes[2] << 8;
    value |= (u32)bytes[3];
    return value;
}
