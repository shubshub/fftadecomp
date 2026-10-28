#include "ffta.h"

typedef struct Unit Unit;
extern s32 func_080C7EA4(const Unit *unit, u8 field);
extern u8 func_080CD9A4(const Unit *unit);

/* Complete [0x081308F4, 0x0813091C): 40 bytes, 18 instructions. */
u8 func_081308F4(const Unit *unit)
{
    if (func_080C7EA4(unit, 27) & 0x800)
        return 1;
    return func_080CD9A4(unit);
}
