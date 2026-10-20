#include "ffta.h"

u8 func_080CCAE8(u8 index);

u8 func_080C9460(u16 code)
{
    u8 index = 0;

    switch (code) {
    case 0xCA:
        index = 0;
        break;
    case 0xCB:
        index = 2;
        break;
    case 0xCC:
        index = 5;
        break;
    case 0xCD:
        index = 7;
        break;
    case 0xCE:
        index = 10;
        break;
    case 0xCF:
        index = 12;
        break;
    case 0xD0:
        index = 14;
        break;
    case 0xD1:
        index = 16;
        break;
    case 0xD2:
        index = 18;
        break;
    }
    return func_080CCAE8(index);
}
