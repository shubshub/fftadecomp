#include "ffta.h"

/* 0x080258C4..0x080258F8: 52 bytes. */
extern u8 func_080CD50C(const void *unit);

u16 func_080258C4(const void *unit, u16 value)
{
    u8 category = func_080CD50C(unit);

    if (category == 10) {
        if (value & 1)
            value++;
        value >>= 1;
    } else if (category == 4) {
        value *= 2;
    }
    return value;
}
