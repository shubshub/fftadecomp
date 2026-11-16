#include "ffta.h"

extern s32 abs(s32 value);

extern int func_0809D79C(s8 x, s8 y);
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u32 func_0809FEF0(void *unit, s8 source_x, s8 source_y, s8 target_x,
                         s8 target_y, u16 entry, u8 alternate);
extern s32 func_0812E1A8(void *unit, u8 from_x, u8 from_y, u8 to_x, u8 to_y,
                         u16 item, u8 flags);
extern u16 func_080B7C50(void *object, u16 first, u16 second, u8 mode);

/* The absolute height difference between two tiles.  The ROM has this block
 * twice, instruction for instruction with the same result registers:
 * 0x080A014E-0x080A0170 here and
 * 0x080A035A-0x080A037C in func_080A0254 (src/080A0254.c), and this macro
 * text reproduces both functions. */
#define HEIGHT_DIFFERENCE(out, from_x, from_y, to_x, to_y)             \
    do {                                                               \
        (out) = func_0801CC18((from_x), (from_y));                     \
        (out) = abs((out) - func_0801CC18((to_x), (to_y)));            \
    } while (0)

/* Complete [0x080A0014, 0x080A0252): 574 bytes, 272 instructions, one
 * literal word (0xFF3F).
 * f0b557464e464546e0b486b00390181c0e9d0f9b109c119e0906090e8a461206120e
 * 049200062d061b041f0c2404240c05943606360e010e884600162a0e91462d16291c
 * fdf7a0fb002800dcd5e053461d06281604990c062116fdf795fb002800dccae04046
 * 49467cf7fefd0006002800d1c2e0404649467cf73cfe0006010e01200840002800d0
 * b7e008200840002800d0b2e0002f0ad0381c04212cf04efe80210140002900d00027
 * 002f0fd129162216444623061b164d462806001600900598019002960398fff708ff
 * afe0381c0b212cf033fe002805d1c24503d10499494500d189e04a46009201970220
 * 029003985146049a43468ef04cf8061c002e7bd0012e00d191e00398391c059a0023
 * 17f094fd0004060c381c05212cf00efe041c7f200440381c04212cf007fe071c104b
 * 181c0740002c11d0504604997cf761fd0006050e404649467cf75bfd0006000e281a
 * 002800da4042a0424ddc7020304020282ad0202806dc002809d0102807d05be03fff
 * 0000302802d040283ed054e054464546601b002800da40420004010c049a4b46d01a
 * 002800da40420004000c002901d0002827d138040214002a3cd0002344465546611b
 * 28e051464246881a002800da40420004010c049b4c46181b002800da40420004020c
 * 08041304011c994201db0b0c00e01b0c1004814203d019043804814218dd002017e0
 * 38040214002a12d0002345465046291a002900da49424c46049d601b002800da4042
 * 0818904200dc0123181c00e0012006b038bc9846a146aa46f0bc02bc0847
 */
s32 func_080A0014(void *context, u8 from_x, u8 from_y,
                  u8 to_x, u8 to_y, u16 action, u16 parameter, u8 flags)
{
    u8 terrain;
    s32 properties;
    s16 height_limit;
    s16 range;

    if (func_0809D79C(to_x, to_y) <= 0)
        return 0;
    if (func_0809D79C(from_x, from_y) <= 0)
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
        return func_0809FEF0(context, from_x, from_y, to_x, to_y,
                             parameter, flags);

    if (!func_080CCD50(action, 11) && from_x == to_x && from_y == to_y)
        return 0;
    /* One variable holds both call results: the ROM moves this one into r6
     * (0x080A0110), where the func_080B7C50 value lives (0x080A012A); a
     * separate local stays in r0 and the function compiles to 552 bytes. */
    properties = func_0812E1A8(context, from_x, from_y, to_x, to_y, action, 2);
    if (!properties)
        return 0;
    if (properties == 1)
        return 1;

    properties = func_080B7C50(context, action, parameter, 0);
    height_limit = func_080CCD50(action, 5) & 0x7f;
    range = func_080CCD50(action, 4) & 0xff3f;
    if (height_limit) {
        s32 height;

        HEIGHT_DIFFERENCE(height, from_x, from_y, to_x, to_y);
        if (height > height_limit)
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
            if (range)
                return (abs(to_x - from_x) +
                        abs(to_y - from_y))
                    <= range;
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
            if (dx == dy || distance > range)
                return 0;
        }
        break;
    case 0x40:
        if (range)
            return (abs(to_x - from_x) +
                    abs(to_y - from_y))
                <= range;
        break;
    }
    return 1;
}
