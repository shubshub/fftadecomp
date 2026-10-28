#include "ffta.h"

/* 08002BB8..08002BDE: 38 bytes. */
s32 func_08002BB8(const u16 *first, const u16 *second)
{
    do {
        if (*first > *second)
            return 1;
        if (*first < *second++)
            return -1;
    } while (*first++ != 0);
    return 0;
}
