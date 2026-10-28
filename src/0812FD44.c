#include "ffta.h"

/* 0x0812FD44..0x0812FDDA: 150 bytes, 69 reachable instructions. */
typedef struct Unit Unit;
extern u32 func_080CCD50(u16, u8);
extern u16 func_0812F410(const Unit *, u32);
extern u16 func_0812F48C(const Unit *, s16, u16, u16, u16);
extern u16 func_0812F528(const Unit *, u32, s16);
extern u8 func_0812F6E0(const Unit *);
extern s16 func_0812F690(const Unit *, u16, u16, s16);

s16 func_0812FD44(const Unit *unit, const Unit *target, u16 identifier,
                  u16 level, u16 option)
{
    u32 category;
    u16 value;

    if (identifier == 0 || func_080CCD50(identifier, 29))
        category = 0;
    else
        category = 1;
    value = func_0812F410(unit, category);
    value = func_0812F48C(unit, (s16)value, identifier, level, option);
    value = func_0812F528(unit, category, (s16)value);
    if (identifier == 0x88 && func_0812F6E0(target) == 1)
        value *= 2;
    return func_0812F690(unit, identifier, level, (s16)value);
}
