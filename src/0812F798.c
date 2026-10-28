#include "ffta.h"

/* 0x0812F798..0x0812F872: 218 bytes, 100 reachable instructions. */
typedef struct Unit Unit;
extern u8 func_080CDAF4(const Unit *);
extern u8 func_080CDB0C(const Unit *);
extern u8 func_080CD92C(const Unit *);
extern u8 func_080CD95C(const Unit *);
extern u8 func_080CD9D4(const Unit *);
extern u8 func_080CDC74(const Unit *);
extern u8 func_080CDC8C(const Unit *);
extern u8 func_080CDC44(const Unit *);
extern u8 func_080CDC5C(const Unit *);

s32 func_0812F798(const Unit *unit, s32 value, u8 mode)
{
    if (func_080CDAF4(unit) && mode == 1)
        value = (value * 358) >> 8;
    if (func_080CDB0C(unit) && mode == 0)
        value = (value * 358) >> 8;
    if (func_080CD92C(unit))
        value = (value * 460) >> 8;
    if (func_080CD95C(unit))
        value = (value * 25) >> 8;
    if (func_080CD9D4(unit))
        value = (value * 358) >> 8;
    if (func_080CDC74(unit) && mode == 1)
        value = (value * 358) >> 8;
    if (func_080CDC8C(unit) && mode == 1)
        value = (value * 179) >> 8;
    if (func_080CDC44(unit) && mode == 0)
        value = (value * 358) >> 8;
    if (func_080CDC5C(unit) && mode == 0)
        value = (value * 179) >> 8;
    return value;
}
