#include "ffta.h"

/* 08013AAC..08013ACC: 32 bytes, 16 instructions. */
u8 func_08013AAC(u8 value, u16 flags)
{
    if (flags & 2)
        return value;
    return value + 2;
}
