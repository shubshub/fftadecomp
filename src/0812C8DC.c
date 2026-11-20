#include "positioned_equipment.h"

extern s32 func_0812F0D8(const void *unit, u16 *entries);

/* Inlined copy of func_0812EF94 (src/0812EF94.c). */
static inline s32 positioned_chance(struct Unit *source, struct Unit *target, u16 entry,
                                    u8 mode, u8 option)
{
    s32 result = func_0812C7F4(source, target, entry, (s8)source->x, (s8)source->y,
                               (s8)target->x, (s8)target->y, (s8)target->direction,
                               mode, option);

    if (result != 0 && func_080CDA64(target))
        result = 100;
    return result;
}

/* 0812C8DC..0812C95E, 130 bytes. */
s32 func_0812C8DC(const void *source, const void *target, u32 mode, u32 unused)
{
    u8 position_mode = mode;
    u16 entries[2];
    u16 entry;

    func_0812F0D8(source, entries);
    entry = entries[0];
    return positioned_chance((struct Unit *)source, (struct Unit *)target, entry,
                             position_mode == 1, 1);
}
