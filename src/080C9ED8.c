#include "ffta.h"

u32 func_080C9ED8(u8 selector)
{
    switch (selector) {
    case 1:
        return 0x8E;
    case 2:
        return 0x4D;
    case 3:
        return 0x5F;
    case 4:
        return 0x55;
    case 5:
        return 0x58;
    case 6:
        return 8;
    case 7:
        return 0x16;
    case 8:
        return 9;
    case 9:
        return 0x0D;
    case 10:
        return 0x0B;
    case 11:
        return 0x0A;
    case 12:
        return 0x0A;
    case 13:
        return 9;
    case 14:
        return 9;
    case 15:
        return 9;
    case 16:
        return 9;
    case 17:
        return 0x0A;
    case 18:
        return 9;
    case 19:
        return 0x0B;
    case 20:
        return 0x0B;
    case 21:
        return 0x11;
    case 22:
        return 0x0B;
    case 23:
        return 9;
    default:
        return 0;
    }
}
