#include "ffta.h"

extern s32 abs(s32 value);

extern int func_0809D79C(s8 x, s8 y);
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u16 func_080B7C50(void *object, u16 first, u16 second, u8 mode);
extern u32 func_0809FEF0(void *unit, s8 source_x, s8 source_y, s8 target_x,
                         s8 target_y, u16 entry, u8 alternate);

/* The absolute height difference between two tiles.  The ROM has this block
 * twice, instruction for instruction with the same result registers:
 * 0x080A035A-0x080A037C here and
 * 0x080A014E-0x080A0170 in func_080A0014 (src/080A0014.c), and this macro
 * text reproduces both functions. */
#define HEIGHT_DIFFERENCE(out, from_x, from_y, to_x, to_y)             \
    do {                                                               \
        (out) = func_0801CC18((from_x), (from_y));                     \
        (out) = abs((out) - func_0801CC18((to_x), (to_y)));            \
    } while (0)

/* Complete [0x080A0254, 0x080A0466): 530 bytes, 251 instructions, one
 * literal word (0xFF3F).
 * f0b557464e464546e0b487b00390181c0f9d109b119c129e0906090e89461206120e
 * 924600062d061b041f0c2404240c04943606360e0596060e0016290e88462d16291c
 * fdf780fa002800dcc0e04a461506281653461c062116fdf775fa002800dcb5e0301c
 * 41467cf7defc0006002800d1ade0301c41467cf71cfd0006010e01200840002800d0
 * a2e008200840002800d09de0002f0ad0381c04212cf02efd80210140002900d00027
 * 002f0fd12916221633061b164446200600160090049d0195059802900398fff7e8fd
 * 99e00398391c049a012317f091fc0004000c0690381c08212cf00afd041c2404240c
 * 381c07212cf003fd071c1249081c074024042414002c11d0484651467cf75bfc0006
 * 050e301c41467cf755fc0006000e281a002800da4042a04252dc7020069a10402028
 * 2fd0202807dc00280ad0102808d05ee000003fff0000302802d0402841d056e04b46
 * 981b002800da40420004010c54464546601b002800da40420004000c002901d00028
 * 2bd138040214002a3fd000234846311a002900da494244465546601b2ce04946881b
 * 002800da40420004010c52464346d01a002800da40420004020c08041304011c9942
 * 01db0b0c00e01b0c1004814203d019043804814217dd002016e038040214002a11d0
 * 00234c46311b002900da494245465446281b002800da40420818904200dc0123181c
 * 00e0012007b038bc9846a146aa46f0bc02bc0847
 */
s32 func_080A0254(void *object, u8 source_x, u8 source_y,
                  u8 destination_x, u8 destination_y,
                  u16 ability, u16 parameter, u8 mode)
{
    u8 flags;
    u16 effect;
    s16 height_limit;
    s16 range;

    if (func_0809D79C(destination_x, destination_y) <= 0)
        return 0;
    if (func_0809D79C(source_x, source_y) <= 0)
        return 0;
    if (!func_0801CC7C(destination_x, destination_y))
        return 0;
    flags = func_0801CD08(destination_x, destination_y);
    if (flags & 1)
        return 0;
    if (flags & 8)
        return 0;
    if (ability != 0) {
        if (func_080CCD50(ability, 4) & 0x80)
            ability = 0;
    }
    if (ability == 0)
        return func_0809FEF0(object, source_x, source_y,
                             destination_x, destination_y, parameter, mode);

    effect = func_080B7C50(object, ability, parameter, 1);
    height_limit = func_080CCD50(ability, 8);
    range = func_080CCD50(ability, 7) & 0xff3f;
    if (height_limit != 0) {
        s32 height;

        HEIGHT_DIFFERENCE(height, source_x, source_y,
                          destination_x, destination_y);
        if (height > height_limit)
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
        if (range != 0)
            return abs(destination_x - source_x)
                + abs(destination_y - source_y) <= range;
        break;
    }
    case 0x20: {
        s16 x_distance = abs(source_x - destination_x);
        s16 y_distance = abs(source_y - destination_y);
        s16 maximum;

        if (x_distance >= y_distance)
            maximum = x_distance;
        else
            maximum = y_distance;
        if (x_distance == y_distance || maximum > range)
            return 0;
        break;
    }
    case 0x40:
        if (range != 0)
            return abs(destination_x - source_x)
                + abs(destination_y - source_y) <= range;
        break;
    }
    return 1;
}
