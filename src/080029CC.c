#include "ffta.h"

/* 0x080029CC..0x08002A08: 60 bytes / 30 instructions. */
s32 func_080029CC(const u8 *first, const u8 *second, u32 count)
{
    while (count-- != 0) {
        if (*first > *second)
            return 1;
        if (*first < *second++)
            return -1;
        if (*first++ == 0)
            break;
    }
    return 0;
}
