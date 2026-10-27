#include "ffta.h"

extern u8 func_0801CC18(u8 column, u8 row);
extern u32 func_0812E130(void *unit, u32 first, u32 second);
extern u8 func_0812E3B0(void *unit);
extern u8 func_0812EE98(void *unit, u16 item);
extern u8 func_0812EED0(void *unit, u16 item);

static inline s32 absolute(s32 value)
{
    if (value < 0)
        value = -value;
    return value;
}

static inline s32 distance(u8 from_x, u8 from_y, u8 to_x, u8 to_y)
{
    return absolute(to_x - from_x) + absolute(to_y - from_y);
}

/* Complete target: 0x0812E1A8..0x0812E366, 446 bytes. */
s32 func_0812E1A8(void *unit, u8 from_x, u8 from_y, u8 to_x, u8 to_y,
                  u16 item, u8 flags)
{
    u8 from_height = func_0801CC18(from_x, from_y);
    s32 height_delta = func_0801CC18(to_x, to_y) - from_height;
    u8 type;

    if (flags & 8)
    {
        if (!func_0812E130(unit, 0, 4))
            return 0;
        if (distance(from_x, from_y, to_x, to_y) <= func_0812E3B0(unit))
            return 1;
        return 0;
    }
    if (flags & 2)
        return -1;

    type = func_0812EE98(unit, item);
    if (type == 15)
    {
        if (distance(from_x, from_y, to_x, to_y) <= 1)
        {
            if (height_delta >= -4 && height_delta <= 3)
                return 1;
        }
        else if (distance(from_x, from_y, to_x, to_y) <= 2)
        {
            s32 middle_x;
            s32 middle_y;
            s32 middle_delta;

            if (from_x != to_x && from_y != to_y)
                return 0;

            if (from_x == to_x)
            {
                middle_x = from_x;
                middle_y = (to_y + from_y) / 2;
            }
            else
            {
                middle_x = (to_x + from_x) / 2;
                middle_y = to_y;
            }

            middle_delta = func_0801CC18(middle_x, middle_y) - from_height;
            if (middle_delta < 0)
            {
                if (height_delta >= -3 && height_delta <= 2)
                    return 1;
            }
            else if (middle_delta < 1)
            {
                if (height_delta >= -2 && height_delta <= 2)
                    return 1;
            }
            else if (middle_delta < 2)
            {
                if (height_delta >= -1 && height_delta <= 2)
                    return 1;
            }
            else if (middle_delta < 3)
            {
                if (height_delta >= 1 && height_delta <= 2)
                    return 1;
            }
            else if (middle_delta < 4)
            {
                if (height_delta == 2)
                    return 1;
            }
        }
    }
    else if (type == 19 || type == 14 || type == 13)
    {
        if (distance(from_x, from_y, to_x, to_y) <= func_0812EED0(unit, item))
            return 1;
    }
    else if (distance(from_x, from_y, to_x, to_y) <= 1)
    {
        if (height_delta >= -3 && height_delta <= 2)
            return 1;
    }
    return 0;
}
