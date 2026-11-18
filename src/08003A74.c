#include "ffta.h"

/* 0x08003A74-0x08003A80: 12 bytes. */
u32 func_08003A74(u32 packed)
{
    u16 field = (packed >> 3) & 0x1F00;

    return field;
}
