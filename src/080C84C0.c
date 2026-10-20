#include "ffta.h"

u8 func_080C84C0(const void *object)
{
    const u8 *record = object;
    u8 result = 0;

    if (record != 0 &&
        (record[4] == 0x52 || record[4] == 0x54 || record[4] == 0x53 ||
         record[4] == 0x1E || record[4] == 0x1F ||
         (u8)(record[4] - 0x39) <= 0x0D))
        result = 1;
    return result;
}
