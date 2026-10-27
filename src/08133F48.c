#include "ffta.h"

/* Complete [0x08133F48, 0x08133F6E): 38 bytes, 19 instructions. */
u32 func_08133F48(u16 value, const u16 *entries, s32 count)
{
    s32 index;

    for (index = 0; index < count; ++index, ++entries) {
        if (value == *entries)
            return 1;
    }
    return 0;
}
