#include "ffta.h"

/* Target: [0x0812D398, 0x0812D424), 140 bytes. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit;

extern u32 func_080C92F0(void *unit, u32 selector);
extern s32 func_080C7EA4(const void *unit, u32 selector);

s32 func_0812D398(Unit *source, Unit *target, s32 count)
{
    s32 rate;
    s32 limit;
    s32 value;

    value = func_080C92F0(target, 0x16);
    if ((value & 0x80) || (target->flags & 0x6000) || count <= 1)
        return 0;
    rate = func_080C7EA4(source, 0x3C) * 10 + (50 - func_080C7EA4(source, 0x39));
    if (rate <= 0)
        rate = 1;
    limit = (u32)(func_080C7EA4(target, 0x14) * rate) / 100;
    value = 100 - (limit - func_080C7EA4(target, 0x13)) * 100 / limit;
    if (value < 0)
        value = 0;
    if (value > 100)
        value = 100;
    return 100 - value;
}
