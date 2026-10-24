#include "ffta.h"

/* 0x08003A80-0x08003A88: 8 bytes. */
u32 func_08003A80(u32 packed)
{
    return (packed >> 12) & 0x0C;
}
