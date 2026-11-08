#include "ffta.h"

extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete target [0x0805CF00, 0x0805CF3C): 60 bytes. */
s16 func_0805CF00(u16 start, u16 end, u16 width, u16 position)
{
    if (position >= width)
        return (s16)end;

    {
        s16 value = start;
        s16 limit = end;

        value += func_081426B8((limit - value) * position, width);
        return value;
    }
}
