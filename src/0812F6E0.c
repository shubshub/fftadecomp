#include "ffta.h"

extern u32 func_080C7EA4(void *unit, u8 field);

u8 func_0812F6E0(void *unit)
{
    switch (func_080C7EA4(unit, 3)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return 0;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        return 1;
    default:
        return 2;
    }
}
