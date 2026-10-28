#include "ffta.h"

u8 func_080184D0(u8 kind)
{
    u8 result = 0;

    if (kind == 1 || kind == 2 ||
        kind == 0x10 || kind == 0x11 || kind == 0x12 ||
        kind == 0x13 || kind == 0x14 || kind == 0x15 ||
        kind == 0x16 || kind == 0x17 || kind == 0x18 ||
        kind == 0x19 || kind == 0x1A)
        result = 1;

    return result;
}
