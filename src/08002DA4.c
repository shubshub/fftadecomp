#include "ffta.h"

void func_08002DA4(const u8 *source, u8 *destination, s16 size)
{
    size >>= 1;

    while (--size != -1) {
        u8 first = *source++;
        *destination++ = *source++;
        *destination++ = first;
    }
}
