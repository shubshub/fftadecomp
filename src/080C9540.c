#include "ffta.h"

extern u8 g_state_02000000[];

u8 func_080C9540(u16 bitIndex)
{
    const u8 *flags = g_state_02000000 + 0x1F70 + (bitIndex >> 3);
    u16 bit = bitIndex & 7;
    u8 mask = 1;

    mask <<= bit;
    if ((*flags & mask) != 0)
        return 1;
    return 0;
}
