#include "ffta.h"

extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern const u32 data_0851D0F4[];

/* Complete [0x080CB5A8, 0x080CB634): 140 bytes, 61 instructions. */
u8 func_080CB5A8(u8 unit, u16 ability)
{
    u8 category = func_080C8570(unit, unit, 1);
    u32 mask = data_0851D0F4[func_080C8570(unit, unit, 0x24)];
    u8 type = func_080CA7A4(ability, 3);

    if (type == 0x16)
        return category == 4;

    if (!(mask & (1 << (type - 1))))
        return 0;

    if ((type == 0x19 || type == 0x17) &&
        (ability == 0x137 || ability == 0x13C || ability == 0x11F) &&
        category != 4)
        return 0;

    return 1;
}
