#include "ffta.h"

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Owner {
    struct Unit *unit;
};

struct GroupEntry {
    struct Owner *owner;
    u8 unknown_04[0x324];
};

struct Group {
    struct GroupEntry entries[13];
    u16 count;
};

extern s32 abs(s32 value);
extern u32 func_08002804(void);
extern u8 func_080C8280(const void *unit);
extern u8 func_080CD92C(const void *unit);
extern u8 func_0809D6BC(s8 dx, s8 dy);

/* Complete 0x080BE9F0..0x080BEAC8: 216 bytes, 101 instructions. */
s8 func_080BE9F0(struct Group *group, struct Owner *excluded, s8 x, s8 y)
{
    u8 direction = (s16)func_08002804() % 4;
    s32 nearest = 0x1000;
    s32 i;

    for (i = 0; i < group->count; i++) {
        struct Unit *unit;
        s32 dx;
        s32 dy;
        s32 x_distance;
        s32 distance;

        if (group->entries[i].owner == excluded)
            continue;
        if (func_080C8280(group->entries[i].owner->unit))
            continue;
        if (func_080CD92C(group->entries[i].owner->unit))
            continue;

        unit = group->entries[i].owner->unit;
        dx = unit->x - x;
        x_distance = abs(dx);
        dy = unit->y - y;
        distance = x_distance + abs(dy);
        if (distance < nearest) {
            nearest = distance;
            direction = func_0809D6BC(dx, dy);
        }
    }
    return direction;
}
