#include "ffta.h"

typedef struct Unit Unit;
extern u32 func_080CCD50(u16 identifier, u8 field);
extern s32 func_0812F5E0(const Unit *unit, u16 level, u32 field);

static inline u8 alternate_field(u16 identifier)
{
    if (identifier == 0 || func_080CCD50(identifier, 29))
        return 0;
    return 1;
}

/* Complete [0x0812F690, 0x0812F6DE): 78 bytes, 37 instructions. */
s16 func_0812F690(const Unit *unit, u16 identifier, u16 level, s16 value)
{
    if (alternate_field(identifier) != 0)
        value += func_0812F5E0(unit, level, 12);
    else
        value += func_0812F5E0(unit, level, 10);
    return value;
}
