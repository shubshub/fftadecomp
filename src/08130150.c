#include "ffta.h"

/* Complete 0x08130150..0x08130200, 176 bytes, 78 instructions.
 * f0 b5 47 46 80 b4 81 b0 06 1c 88 46 12 04 15 0c
 * 1b 06 1f 0e fb 2d 01 d1 19 20 40 e0 fc 2d 01 d1
 * 32 20 3c e0 fd 2d 01 d1 96 20 38 e0 00 2d 05 d0
 * 28 1c 1d 21 9c f7 e4 fd 00 28 01 d0 00 24 00 e0
 * 01 24 30 1c 21 1c ff f7 3b f9 01 1c 09 04 09 14
 * 00 20 00 90 30 1c 2a 1c 00 23 ff f7 6f f9 02 1c
 * 12 04 12 14 30 1c 21 1c ff f7 b6 f9 00 22 02 2f
 * 00 d1 01 22 41 46 ff f7 a1 ff 04 1c 28 1c 21 21
 * 9c f7 be fd 60 43 64 21 12 f0 6e fa 04 1c 00 2c
 * 00 dc 01 24 05 48 84 42 00 dd 04 1c 20 1c 01 b0
 * 08 bc 98 46 f0 bc 02 bc 08 47 00 00 e7 03 00 00
 */

extern u32 func_080CCD50(u16 identifier, u8 selector);
extern s32 func_0812F410(void *actor, u16 alternate);
extern s16 func_0812F48C(void *actor, s16 value, u16 identifier,
                        u16 level, u16 option);
extern s32 func_0812F528(void *actor, u8 mode, s16 value);
extern s32 func_0813010C(s32 value, void *target, u8 option);

s32 func_08130150(void *actor, void *target, u16 identifier, u8 option)
{
    u32 category;
    u16 value;
    s32 result;

    if (identifier == 251)
        return 25;
    if (identifier == 252)
        return 50;
    if (identifier == 253)
        return 150;

    if (identifier == 0 || func_080CCD50(identifier, 29))
        category = 0;
    else
        category = 1;

    value = func_0812F410(actor, category);
    value = func_0812F48C(actor, (s16)value, identifier, 0, 0);
    result = func_0813010C(func_0812F528(actor, category, (s16)value),
                          target, option == 2);
    result = (s32)(result * func_080CCD50(identifier, 33)) / 100;
    if (result <= 0)
        result = 1;
    if (result > 999)
        result = 999;
    return result;
}
