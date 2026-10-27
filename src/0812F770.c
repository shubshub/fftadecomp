#include "ffta.h"

typedef struct Unit Unit;
extern u8 func_080CD50C(const Unit *unit);

/* Complete [0x0812F770, 0x0812F798): 40 bytes, 19 instructions. */
s32 func_0812F770(const Unit *unit, s32 value, u8 category)
{
    if (category == 0 && func_080CD50C(unit) == 2)
        return (value * 358) >> 8;
    return value;
}
