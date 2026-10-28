#include "ffta.h"

extern u8 func_08036330(u8 selector);
extern u32 func_08036440(u8 value, u32 mode);

/* 0x08036424 - 28 bytes.
 * Target: 10b50c1c0006000efff780ff0006000e211c00f003f810bc02bc0847
 */
u32 func_08036424(u8 selector, u32 mode)
{
    return func_08036440(func_08036330(selector), mode);
}
