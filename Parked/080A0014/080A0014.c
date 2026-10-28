#include "ffta.h"

extern s32 abs(s32 value);

extern s32 func_0809D79C(s8 x, s8 y);
extern u8 func_0801CC7C(u8 x, u8 y);
extern u8 func_0801CD08(u8 x, u8 y);
extern u8 func_0801CC18(u8 x, u8 y);
extern u32 func_080CCD50(u16 action, u8 property);
extern s32 func_0809FEF0(void *context, s8 from_x, s8 from_y,
                       s8 to_x, s8 to_y, u16 parameter, u8 flags);
extern s32 func_0812E1A8(void *context, u8 from_x, u8 from_y,
                       u8 to_x, u8 to_y, u16 action, s32 mode);
extern u16 func_080B7C50(void *context, u16 action, u16 parameter, s32 mode);

/* Complete [0x080A0014, 0x080A0252): 574 bytes, 272 instructions. */
s32 func_080A0014(void *context, u8 from_x, u8 from_y,
                  u8 to_x, u8 to_y, u16 action, u16 parameter, u8 flags)
{
    u8 terrain;
    s32 properties;
    s32 height_limit;
    u32 range;

    if (func_0809D79C((s8)to_x, (s8)to_y) <= 0)
        return 0;
    if (func_0809D79C((s8)from_x, (s8)from_y) <= 0)
        return 0;
    if (!func_0801CC7C(to_x, to_y))
        return 0;
    terrain = func_0801CD08(to_x, to_y);
    if (terrain & 1)
        return 0;
    if (terrain & 8)
        return 0;

    if (action) {
        if (func_080CCD50(action, 4) & 0x80)
            action = 0;
    }
    if (!action)
        return func_0809FEF0(context, (s8)from_x, (s8)from_y,
                            (s8)to_x, (s8)to_y, parameter, flags);

    if (!func_080CCD50(action, 11) && from_x == to_x && from_y == to_y)
        return 0;
    properties = func_0812E1A8(context, from_x, from_y, to_x, to_y, action, 2);
    if (!properties)
        return 0;
    if (properties == 1)
        return 1;

    properties = func_080B7C50(context, action, parameter, 0);
    height_limit = func_080CCD50(action, 5) & 0x7f;
    range = func_080CCD50(action, 4) & 0xff3f;
    if (height_limit) {
        u8 from_height = func_0801CC18(from_x, from_y);
        u8 to_height = func_0801CC18(to_x, to_y);
        s32 difference = abs(from_height - to_height);

        if (difference > height_limit)
            return 0;
    }

    switch (properties & 0x70) {
    case 0:
    case 0x10:
    case 0x30:
        {
            s16 dx = abs(from_x - to_x);
            s16 dy = abs(from_y - to_y);
            if (dx && dy)
                return 0;
            if ((s16)range)
                return (abs(to_x - from_x) +
                        abs(to_y - from_y))
                    <= (s16)range;
        }
        break;
    case 0x20:
        {
            s16 dx = abs(from_x - to_x);
            s16 dy = abs(from_y - to_y);
            s16 distance;

            if (dx >= dy)
                distance = dx;
            else
                distance = dy;
            if (dx == dy || distance > (s16)range)
                return 0;
        }
        break;
    case 0x40:
        if ((s16)range)
            return (abs(to_x - from_x) +
                    abs(to_y - from_y))
                <= (s16)range;
        break;
    }
    return 1;
}
