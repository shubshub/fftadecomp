#include "ffta.h"

/* 08002C38..08002C4E: 22 bytes. */
void func_08002C38(u16 *destination, const u16 *source)
{
    u16 value;

    do {
        value = (*destination++ = *source++);
    } while (value != 0);
}
