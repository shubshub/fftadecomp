#include "ffta.h"

/* 0x080D5FA4..0x080D5FD8: 52 bytes, 26 instructions. */
s32 func_080D5FA4(const u32 *entries, u16 count)
{
    s16 i;

    for (i = 0; i < count; i++) {
        if (entries[i] == 0) {
            return i;
        }
    }
    return -1;
}
