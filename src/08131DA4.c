#include "ffta.h"

u8 func_08131DA4(u8 *flags, s32 index, u8 second)
{
    s32 byteIndex;
    s32 bitOffset;

    index *= 2;
    if (second)
        index++;
    byteIndex = index >> 3;
    bitOffset = index & 7;
    if ((flags[byteIndex] >> bitOffset) & 1)
        return 1;
    return 0;
}
