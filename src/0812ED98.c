#include "ffta.h"

/* 0x0812ED98..0x0812EDEE: 86 bytes. */
extern u16 func_080CCD50(u16, u8);
extern u8 func_080CD50C(const void *);

s16 func_0812ED98(const void *unit, u16 entry)
{
    s16 value;

    if (entry == 0)
        return 0;
    value = func_080CCD50(entry, 2);
    switch (func_080CD50C(unit)) {
    case 4:
        value *= 2;
        break;
    case 10:
        if (value & 1)
            ++value;
        value >>= 1;
        break;
    }
    return value;
}
