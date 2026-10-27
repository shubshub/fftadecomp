#include "ffta.h"

extern const s16 g_table_08149568[];

/* Target [0x080071E8, 0x08007234): 76 bytes, 31 instructions. */
s16 func_080071E8(s16 degrees)
{
    s32 angle = degrees;

    while ((u32)angle > 359)
    {
        if (angle < 0)
            angle += 360;
        if (angle > 359)
            angle -= 360;
    }

    return g_table_08149568[(angle << 8) / 360];
}
