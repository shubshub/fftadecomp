#include "ffta.h"

extern u8 g_state_02000000[];

void func_080C9574(u16 bitIndex, u16 enabled)
{
    u8 *flags = g_state_02000000 + 0x1F70 + (bitIndex >> 3);
    u16 bit = bitIndex & 7;
    u8 mask = 1;

    mask <<= bit;
    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}
