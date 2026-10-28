#include "ffta.h"

typedef struct {
    u8 unknown_00[0xEA];
    u8 flags;
} Unit;

u8 func_080CDA94(Unit *unit)
{
    const u8 *flags = &unit->flags;
    u32 mask = 0x10;
    u32 value = *flags;
    if (!(value & mask))
        return 0;
    return 1;
}
