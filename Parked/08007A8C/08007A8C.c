/* 0x08007A8C - 54 bytes */
#include "ffta.h"

extern s32 func_080071E8(s16 angle);

s16 func_08007A8C(s16 angle)
{
    s32 numerator = func_080071E8(angle);
    s32 denominator = func_080071E8(angle + 90);

    return (s16)numerator / (s16)denominator;
}
