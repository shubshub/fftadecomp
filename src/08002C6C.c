#include "ffta.h"

/* 08002C6C..08002CB0: 68 bytes. Append up to count UTF-16 code units. */
u16 *func_08002C6C(u16 *destination, const u16 *source, u16 count)
{
    s16 remaining = count;
    u16 *original = destination;

    while (*destination != 0)
        destination++;

    while (--remaining != -1) {
        if ((*destination++ = *source++) == 0)
            break;
    }

    return original;
}
