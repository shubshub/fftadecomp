#include "ffta.h"

/* 08002CB0..08002D04: 84 bytes. Compare bounded halfword strings. */
s32 func_08002CB0(const u16 *left, const u16 *right, s16 count)
{
    while (--count != -1) {
        if (*left > *right)
            return 1;
        if (*left < *right++)
            return -1;
        if (*left++ == 0)
            break;
    }

    return 0;
}
