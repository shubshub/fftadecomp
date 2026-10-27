#include "ffta.h"

typedef struct Unit Unit;
extern u8 func_08134A10(Unit *unit, u32 unknown_1, u32 unknown_2,
                        u32 unknown_3, u32 unknown_4, u32 unknown_5,
                        u8 mode, u32 unknown_7, u8 selector);

/* Complete [0x08134AFC, 0x08134B38): 60 bytes, 29 instructions. */
u8 func_08134AFC(Unit *unit, u32 unknown_1, u16 unknown_2,
                  u8 unknown_3, s16 unknown_4, u32 unknown_5,
                  u8 mode, u8 selector)
{
    return func_08134A10(unit, unknown_1, unknown_2, unknown_3,
                         unknown_4, unknown_5, mode, 0, selector);
}
