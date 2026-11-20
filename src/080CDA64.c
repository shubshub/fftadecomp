#include "positioned_equipment.h"

u8 func_080CDA64(const struct Unit *unit)
{
    u8 mask = 2;
    u8 flags = unit->flags;

    if (!(flags & mask))
        return 0;
    return 1;
}
