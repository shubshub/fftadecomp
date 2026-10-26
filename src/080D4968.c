#include "ffta.h"

/* 0x080D4968..0x080D499C: 52 bytes. */
s16 func_080D4968(const u32 *handles, u16 count)
{
    s16 i;

    for (i = 0; i < count; i++) {
        if (handles[i] == 0)
            return i;
    }
    return -1;
}
