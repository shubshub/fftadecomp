#include "positioned_equipment.h"

/* 0x0812EF94..0x0812F008: 116 bytes. */

s32 func_0812EF94(struct Unit *source, struct Unit *target,
                  u16 entry, u8 mode, u8 option)
{
    s32 result = func_0812C7F4(source, target, entry,
                              (s8)source->x, (s8)source->y,
                              (s8)target->x, (s8)target->y, (s8)target->direction,
                              mode, option);

    if (result != 0 && func_080CDA64(target))
        result = 100;
    return result;
}
