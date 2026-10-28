#include "ffta.h"

/* 08011710..08011744: 52 bytes. */
s16 func_08011710(void *const *entries, u16 count)
{
    s16 index;

    for (index = 0; index < count; index++) {
        if (entries[index] == 0)
            return index;
    }
    return -1;
}
