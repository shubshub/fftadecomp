#include "ffta.h"

void func_08131DD4(u8 *buffer, s32 index)
{
    u8 *flags = buffer + 0x10;
    s32 byteIndex = index >> 3;
    s32 bitOffset = index & 7;

    flags[byteIndex] |= 1 << bitOffset;
}
