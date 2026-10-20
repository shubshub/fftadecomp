#include "ffta.h"

u8 func_080C8228(const void *object)
{
    const u8 *record = object;
    u8 result = 0;

    if (record != 0 && record[7] == 0x18)
        result = 1;
    return result;
}
