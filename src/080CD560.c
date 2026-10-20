#include "ffta.h"

u8 func_080CD560(const void *object, u8 index)
{
    const u8 *record = object;

    if (record != 0) {
        const u8 *flags = record + 0x40;

        if (flags[index] & 0x80)
            return 1;
    }
    return 0;
}
