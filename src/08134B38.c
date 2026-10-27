#include "ffta.h"

typedef struct Unit Unit;

extern u8 func_08134A10(Unit *unit, u32 unknown_1, u32 unknown_2,
                       u32 unknown_3, u32 unknown_4, u32 unknown_5,
                       u8 mode, u32 unknown_7, u8 selector);

/* Target: [0x08134B38, 0x08134B5C), 36 bytes, 17 instructions. */
u8 func_08134B38(Unit *unit)
{
    return func_08134A10(unit, 0, 0, 0, 0, 0, 1, 1, 0);
}
