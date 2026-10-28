#include "ffta.h"

/* 0x0812E5B4..0x0812E6A2: 238 bytes. */
extern u32 func_080C7EA4(void *unit, u32 field);
extern u8 func_080C9540(u32 ability);
extern u8 func_080C8260(void *unit);
extern u8 func_080C8240(void *unit);
extern u8 func_080C95A8(u32 flag);

s32 func_0812E5B4(void *unit, void *other)
{
    s16 chance;

    if (func_080C7EA4(unit, 4) > 82) {
        u32 ability = 600;
        switch (func_080C7EA4(unit, 1)) {
        case 9:
            ability = 601;
            break;
        case 4:
            ability = 602;
            break;
        case 12:
            ability = 603;
            break;
        case 94:
            ability = 604;
            break;
        case 10:
            break;
        default:
            return 0;
        }
        if (!func_080C9540(ability))
            return 0;
        if (func_080C8260(unit))
            return 0;
        if (func_080C8240(unit))
            return 0;
    }
    if (func_080C95A8(13))
        return 0;

    chance = 2 * (func_080C7EA4(other, 6) - func_080C7EA4(unit, 6)) + 10;
    if (chance <= 0)
        chance = 1;
    if (chance > 100)
        chance = 100;

    if (func_080C7EA4(unit, 6) > 49) {
        if (func_080C7EA4(unit, 7) + chance > 99)
            chance = 99 - func_080C7EA4(unit, 7);
    }
    return chance;
}
