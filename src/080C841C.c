#include "ffta.h"

u8 func_080C93F0(u8 index);

u8 func_080C841C(const void *object)
{
    const u8 *record = object;

    switch (func_080C93F0(record[7])) {
    case 1:
    case 4:
    case 6:
    case 7:
    case 10:
    case 12:
    case 16:
    case 21:
    case 24:
    case 30:
        return 1;
    default:
        return 0;
    }
}
