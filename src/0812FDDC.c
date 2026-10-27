#include "ffta.h"

typedef struct Unit Unit;
extern u32 func_080CCD50(u16 identifier, u8 field);
extern s32 func_0812F704(const Unit *unit, u8 mode);
extern s32 func_0812F770(const Unit *unit, s32 value, u8 mode);
extern s32 func_0812F798(const Unit *unit, s32 value, u8 mode);
extern s32 func_0812F874(const Unit *unit, s32 value, u8 mode);

/* Complete [0x0812FDDC, 0x0812FE26): 74 bytes, 32 instructions. */
s32 func_0812FDDC(const Unit *source, const Unit *target, u16 identifier)
{
    u32 category;
    s32 value;

    if (identifier == 0 || func_080CCD50(identifier, 29))
        category = 0;
    else
        category = 1;
    value = func_0812F704(target, category);
    value = func_0812F770(target, value, category);
    value = func_0812F798(target, value, category);
    value = func_0812F874(target, value, category);
    return value;
}
