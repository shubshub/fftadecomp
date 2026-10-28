#include "ffta.h"

extern u32 func_080C92F0(void *unit, u8 selector);
extern u8 func_080B7C94(u16 ability, u16 parameter, s32 mode);

/* 0x080B7DC8..0x080B7E06: 62 bytes. */
u8 func_080B7DC8(void *unit, u16 ability, u16 parameter, s32 mode)
{
    if (unit != 0 && (func_080C92F0(unit, 0x28) & 4)) {
        if (mode == 0)
            return 4;
        return 1;
    }
    return func_080B7C94(ability, parameter, mode);
}
