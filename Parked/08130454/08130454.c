#include "ffta.h"

extern u8 func_08130868(void *source, void *target);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern s32 func_0812FE38(void *source, void *target, u16 action, u16 equipment,
                        u16 attribute, u8 mode, u8 extra);
extern s32 func_080C7EA4(const void *unit, u32 field);

/* 0x08130454..0x081304E0: 140 bytes. */
s16 func_08130454(void *source, void *target, s32 total)
{
    u16 equipment[2];
    s32 value;
    s32 factor;
    u32 percentage;
    u8 mode;
    u16 selected;

    if (func_08130868(source, target))
        return 0;
    func_0812F0D8(source, equipment);
    selected = equipment[0];
    mode = 2;
    value = func_0812FE38(source, target, 0, selected, 0, mode, 0);
    if (total)
        factor = func_080C7EA4(source, 38) * 4 + 10;
    else
        factor = 10;
    percentage = (u32)total + 100;
    value = (s32)((u32)factor * value * percentage);
    value /= 1000;
    if (value > 999)
        value = 999;
    if (value < -999)
        value = -999;
    return value;
}
