#include "ffta.h"

extern u32 func_080C92F0(void *unit, u32 selector);
extern s32 func_080CA7A4(u16 entry, u8 selector);

/* Complete [0x0812EE98, 0x0812EECE): 54 bytes, 25 instructions.
 * 10b509040c0c002808d028219af724fa04210140002901d0132009e0002c06d0
 * 201c03219bf772fc0006000e00e0112010bc02bc0847
 */
u8 func_0812EE98(void *unit, u16 entry)
{
    u8 value;

    if (unit != 0 && (func_080C92F0(unit, 0x28) & 4))
        return 0x13;
    if (entry != 0)
        value = func_080CA7A4(entry, 3);
    else
        value = 0x11;
    return value;
}
