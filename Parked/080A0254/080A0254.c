#include "ffta.h"

extern s32 abs(s32 value);

extern s32 func_0809D79C(s8 x, s8 y);
extern u8 func_0801CC7C(u8 x, u8 y);
extern u8 func_0801CD08(u8 x, u8 y);
extern u8 func_0801CC18(u8 x, u8 y);
extern u32 func_080CCD50(u16 ability, u8 selector);
extern u16 func_080B7C50(void *object, u16 ability, u16 parameter, s32 mode);
extern s32 func_0809FEF0(void *object, s8 source_x, s8 source_y,
                         s8 destination_x, s8 destination_y,
                         u16 parameter, u8 mode);

/* 0x080A0254..0x080A0466: 530 bytes. */
s32 func_080A0254(void *object, u8 source_x, u8 source_y,
                   u8 destination_x, u8 destination_y,
                   u16 ability, u16 parameter, u8 mode)
{
    u8 flags;
    u16 effect;
    u16 height_field;
    s16 height_limit;
    u32 range;

    if (func_0809D79C((s8)destination_x, (s8)destination_y) <= 0)
        return 0;
    if (func_0809D79C((s8)source_x, (s8)source_y) <= 0)
        return 0;
    if (!func_0801CC7C((u8)destination_x, (u8)destination_y))
        return 0;
    flags = func_0801CD08((u8)destination_x, (u8)destination_y);
    if (flags & 1)
        return 0;
    if (flags & 8)
        return 0;
    if (ability != 0) {
        if (func_080CCD50(ability, 4) & 0x80)
            ability = 0;
    }
    if (ability == 0)
        return func_0809FEF0(object, (s8)source_x, (s8)source_y,
                             (s8)destination_x, (s8)destination_y, parameter, mode);

    effect = func_080B7C50(object, ability, parameter, 1);
    height_field = func_080CCD50(ability, 8);
    range = func_080CCD50(ability, 7) & 0xff3f;
    height_limit = height_field;
    if (height_limit != 0) {
        s32 difference = func_0801CC18(source_x, source_y)
            - func_0801CC18(destination_x, destination_y);

        if (difference < 0)
            difference = -difference;
        if (difference > height_limit)
            return 0;
    }

    switch (effect & 0x70) {
    case 0:
    case 0x10:
    case 0x30: {
        s16 x_distance = abs(source_x - destination_x);
        s16 y_distance = abs(source_y - destination_y);

        if (x_distance != 0 && y_distance != 0)
            return 0;
        if ((s16)range != 0) {
            return (s16)range >= abs(destination_x - source_x)
                + abs(destination_y - source_y);
        }
        break;
    }
    case 0x20: {
        s16 x_distance = abs(source_x - destination_x);
        s16 y_distance = abs(source_y - destination_y);
        s16 maximum;

        if ((s16)x_distance >= (s16)y_distance)
            maximum = x_distance;
        else
            maximum = y_distance;
        if (x_distance == y_distance || (s16)maximum > (s16)range)
            return 0;
        break;
    }
    case 0x40:
        if ((s16)range != 0) {
            return abs(destination_x - source_x)
                + abs(destination_y - source_y) <= (s16)range;
        }
        break;
    }
    return 1;
}
