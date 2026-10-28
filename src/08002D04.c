#include "ffta.h"

/* 0x08002D04 - 92 bytes. Copy a bounded halfword string and zero-fill the remainder. */
u16 *func_08002D04(u16 *destination, const u16 *source, s16 count)
{
    u16 *start = destination;

    while (--count != -1) {
        if ((*destination++ = *source++) == 0)
            break;
    }
    while (count-- > 0)
        *destination++ = 0;
    return start;
}
