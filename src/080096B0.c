#include "ffta.h"

/* Target: 0x080096B0, 46 bytes. */
int func_080096B0(const void *first, const void *second, int size)
{
    const u8 *left = first;
    const u8 *right = second;

    if (size <= 0)
        return -1;
    do {
        if (*left++ != *right++)
            return 1;
    } while (--size > 0);
    return 0;
}
