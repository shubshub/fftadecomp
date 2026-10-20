#include "ffta.h"

s32 func_080C7EA4(const void *object, u32 selector);

u32 func_080CD584(const void *object)
{
    switch (func_080C7EA4(object, 3)) {
    case 1:
    case 0x17:
        return 0x139;
    case 2:
        return 0x138;
    case 3:
    case 0x14:
        return 0x13A;
    case 4:
        return 0x13B;
    default:
        return 0x13C;
    }
}
