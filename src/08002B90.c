#include "ffta.h"

/* 0x08002B90..0x08002BB8: 40 bytes. */
u16 *func_08002B90(u16 *destination, const u16 *source)
{
    u16 *start = destination;
    u16 value;

    while (*destination != 0)
        destination++;
    do {
        value = (*destination++ = *source++);
    } while (value != 0);
    return start;
}
