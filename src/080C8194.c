#include "ffta.h"

u8 func_080C8194(const void *object, u8 category)
{
    const u8 *record = object;
    u8 result = 0;

    if (record != 0 && record[4] == category)
        result = 1;
    return result;
}
