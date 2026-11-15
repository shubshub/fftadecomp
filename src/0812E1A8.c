#include "ffta.h"

extern u8 func_0801CC18(u8 column, u8 row);
extern s32 func_0812E130(const void *unit, const void *unused, u32 options);
extern u8 func_0812E3B0(const void *selection);
extern u8 func_0812EE98(void *unit, u16 entry);
extern u8 func_0812EED0(void *unit, u16 entry);
extern s32 abs(s32 value);

/* Complete target: 0x0812E1A8..0x0812E366, 446 bytes, 216 instructions.
 *
 * abs is the compiler builtin: the ROM has it expanded in line at every use.
 * The ROM evaluates the distance between the two positions afresh at each of
 * the five tests below (twice in the type 15 block), so it is written out at
 * each one instead of being held in a local.
 */
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
        if (abs(to_x - from_x) + abs(to_y - from_y) <= func_0812E3B0(unit))
            return 1;
        return 0;
    }
    if (flags & 2)
        return -1;

    type = func_0812EE98(unit, item);
    if (type == 15)
    {
        if (abs(to_x - from_x) + abs(to_y - from_y) <= 1)
        {
            if (height_delta >= -4 && height_delta <= 3)
                return 1;
        }
        else if (abs(to_x - from_x) + abs(to_y - from_y) <= 2)
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
        return 0;
    }
    if (type == 19 || type == 14 || type == 13)
    {
        if (abs(to_x - from_x) + abs(to_y - from_y)
            <= func_0812EED0(unit, item))
            return 1;
        return 0;
    }
    if (abs(to_x - from_x) + abs(to_y - from_y) <= 1)
    {
        if (height_delta >= -3 && height_delta <= 2)
            return 1;
    }
    return 0;
}
