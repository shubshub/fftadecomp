#include "ffta.h"

/* 0x08013ACC..0x08013B06: 58 bytes. */
u8 func_08013ACC(u8 value, u16 flags)
{
    u16 related = flags & 0x1C20;

    if (flags & 4) {
        return value * 2;
    }
    if (!related) {
        return value * 2 + 3;
    }
    return value * 2 + 2;
}
