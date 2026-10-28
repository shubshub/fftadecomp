#include "ffta.h"

extern u16 func_0801BB94(s16 x, s16 y, u8 mode, u8 effect, u8 option);

/* 080D8D98..080D8DC0: 40 bytes, 19 instructions. */
u8 func_080D8D98(s16 x, s16 y)
{
    return func_0801BB94(x, y, 4, 16, 4) != 0;
}
