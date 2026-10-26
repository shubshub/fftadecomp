#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x103];
} Unit08068110;

extern Unit08068110 g_state_02000080[24];
extern u8 func_080C8194(Unit08068110 *, u32);

/* Complete [0x08068110, 0x08068158): 72 bytes, 31 instructions. */
u8 func_08068110(void)
{
    Unit08068110 *unit = g_state_02000080;
    u32 count = 0;
    s32 i;

    for (i = 0; i < 24; i++, unit++) {
        if (unit->active && !func_080C8194(unit, 2) && !func_080C8194(unit, 8))
            count++;
    }
    return count;
}
