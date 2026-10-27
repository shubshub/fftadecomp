#include "ffta.h"

extern u32 func_080C92F0(void *unit, u32 selector);
extern s32 func_080CA7A4(u16 entry, u8 selector);

/* Complete [0x0812EED0, 0x0812EF06): 54 bytes, 25 instructions. */
u8 func_0812EED0(void *unit, u16 entry)
{
    u8 value;

    if (unit != 0 && (func_080C92F0(unit, 0x28) & 4))
        return 4;
    if (entry != 0)
        value = func_080CA7A4(entry, 5);
    else
        value = 1;
    return value;
}
