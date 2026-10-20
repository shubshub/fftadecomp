#include "ffta.h"

u8 func_080C81E0(const void *object)
{
    const u8 *record = object;
    u8 result = 0;

    if (record != 0 && record[6] == 3)
        result = 1;
    return result;
}
