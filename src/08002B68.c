#include "ffta.h"

/* 08002B68..08002B90: 40 bytes, 20 instructions. */
u8 *func_08002B68(u8 *destination, const u8 *source)
{
    u8 *start = destination;
    u8 character;

    while (*destination)
        destination++;
    do {
        character = (*destination++ = *source++);
    } while (character != 0);
    return start;
}
