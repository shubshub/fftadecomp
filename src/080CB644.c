#include "ffta.h"

extern s32 func_080CA7A4(u16 entry, u8 selector);

/* Complete [0x080CB644, 0x080CB65A): 22 bytes, 10 instructions. */
u8 func_080CB644(u16 entry)
{
    u32 flags = func_080CA7A4(entry, 7);

    return (flags >> 1) & 1;
}
