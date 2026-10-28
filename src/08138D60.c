#include "ffta.h"

/* Target: complete [0x08138D60, 0x08138DA4), 68 bytes, 28 instructions. */
extern u8 data_02003CB0[];
extern u32 func_0813B480(u32, const void *);

u8 func_08138D60(void)
{
    u8 mask = func_0813B480(0, data_02003CB0) != 0;

    if (func_0813B480(1, data_02003CB0))
        mask |= 2;
    if (func_0813B480(2, data_02003CB0))
        mask |= 4;
    return mask;
}
