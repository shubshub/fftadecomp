#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value;
} Unit;

extern u8 func_08131030(const void *unit);
extern u8 func_080CE3A0(const void *unit);
extern u8 func_080CDCEC(const void *unit);

/* 0812E470..0812E4A8: 56 bytes, 25 instructions. */
u8 func_0812E470(const Unit *unit)
{
    if (func_08131030(unit) && func_080CE3A0(unit))
        return 0;
    if (func_080CDCEC(unit))
        return 0;
    if (unit->value == 0)
        return 0;
    return 1;
}
