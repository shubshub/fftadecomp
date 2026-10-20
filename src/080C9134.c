#include "ffta.h"

s32 func_080C9134(u8 selector)
{
    switch (selector) {
    case 0x2C:
        return 0;
    case 0x2D:
        return 1;
    case 0x2E:
        return 2;
    case 0x2F:
        return 3;
    case 0x30:
        return 4;
    case 0x31:
        return 5;
    case 0x32:
        return 6;
    case 0x33:
        return 7;
    case 0x34:
        return 8;
    case 0x35:
        return 9;
    case 0x36:
        return 10;
    case 0x37:
        return 11;
    case 0x38:
        return 12;
    case 0x39:
        return 13;
    case 0x3E:
        return 14;
    case 0x3F:
        return 15;
    case 0x40:
        return 16;
    case 0x41:
        return 17;
    case 0x42:
        return 18;
    case 0x43:
        return 19;
    default:
        return -1;
    }
}
