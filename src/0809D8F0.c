#include "ffta.h"

/* 0x0809D8F0..0x0809D90A: 26 bytes. */
typedef struct {
    void *unit;
} UnitOwner;

u8 *func_080C7EA4(void *unit, u32 selector);

u8 func_0809D8F0(UnitOwner *owner)
{
    if (*func_080C7EA4(owner->unit, 0x44) != 3)
        return 0;
    return 1;
}
