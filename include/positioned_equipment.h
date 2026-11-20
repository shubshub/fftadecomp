#ifndef GUARD_POSITIONED_EQUIPMENT_H
#define GUARD_POSITIONED_EQUIPMENT_H

#include "ffta.h"

struct Unit {
    u8 unknown_00[0xD6];
    u16 resource;
    u8 unknown_D8[0xEA - 0xD8];
    u8 flags;
    u8 unknown_EB[0xF6 - 0xEB];
    u8 x;
    u8 y;
    u8 direction;
};

s32 func_0812C7F4(struct Unit *source, struct Unit *target, u16 entry,
                  s8 source_x, s8 source_y, s8 target_x, s8 target_y,
                  s8 direction, u32 check_position, u8 option);
u8 func_080CDA64(const struct Unit *unit);
s32 func_0812EF94(struct Unit *source, struct Unit *target, u16 entry,
                  u8 mode, u8 option);
s32 func_0812C8DC(const void *source, const void *target, u32 mode, u32 unused);

#endif
