#include "ffta.h"

/* 0x08061BFC..0x08061C22: 38 bytes, 19 instructions. */
s32 func_08061BFC(const u8 *first, const u8 *second)
{
    while (*first == *second) {
        if (*first == 0 || *second == 0)
            return 0;
        first++;
        second++;
    }
    return *first - *second;
}
