#include "ffta.h"

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0812EE98(void *unit, u16 entry);
extern s32 func_0812E1A8(void *unit, u8 x, u8 y, u8 other_x, u8 other_y,
                         u16 entry, u8 mode);
extern u8 func_0812EED0(void *unit, u16 entry);

/* Complete [0x0809FEF0, 0x080A0012): 290 bytes, 140 instructions.
 * f0b557464e464546e0b487b081460f98109c119d0906090e03911206120e0492
 * 1b061b0e05930006000e82462404270c2d062d0e06951e06350e00068046040e
 * 281c211c7cf7a2fe000600283fd0281c211c7cf7e1fe0006010e012008400028
 * 35d108200840002831d103990806041c049a1506b44201d1454528d04846391c
 * 8ef092ff0006010e081c0d380004000c059e3606b04652461206924601281cd9
 * 13291ad0210e2a0e330e5646300e009001970698002801d0082000e001200290
 * 48468ef0f9f800040014002801d100201fe0012801d101201be04846391c8ef0
 * 7fff0006020e00264046011620160b1a002b00da5b42504601162816081a0028
 * 00da4042191810060016814200dc0126301c07b038bc9846a146aa46f0bc02bc
 * 0847
 */
u32 func_0809FEF0(void *unit, s8 source_x, s8 source_y, s8 target_x,
                  s8 target_y, u16 entry, u8 alternate)
{
    /* A word-sized local for the u8 result: with a u8 local the tests
       compile to the same instructions but the frame is 32 bytes, not the
       ROM's 28. */
    u32 flags;
    u16 type;
    s8 range;
    u8 eligible;
    s32 dx;
    s32 dy;

    if (!func_0801CC7C(target_x, target_y))
        return 0;
    flags = func_0801CD08(target_x, target_y);
    if (flags & 1)
        return 0;
    if (flags & 8)
        return 0;
    if (source_x == target_x && source_y == target_y)
        return 0;
    type = func_0812EE98(unit, entry);
    if (type != 13 && type != 14 && type != 19) {
        s16 result = func_0812E1A8(unit, source_x, source_y, target_x,
                                   target_y, entry, alternate ? 8 : 1);

        if (result == 0)
            return 0;
        if (result == 1)
            return 1;
    }
    range = func_0812EED0(unit, entry);
    eligible = 0;
    dx = target_x - source_x;
    if (dx < 0)
        dx = -dx;
    dy = target_y - source_y;
    if (dy < 0)
        dy = -dy;
    if (dx + dy <= range)
        eligible = 1;
    return eligible;
}
