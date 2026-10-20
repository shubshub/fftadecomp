#include "ffta.h"

extern u8 g_state_02000000[];

u32 func_08122EC0(void *context, const u8 *script)
{
    u32 value = script[1] | (script[2] << 8);
    u8 index = g_state_02000000[0x219C]++;

    ((u16 *)(g_state_02000000 + 0x2194))[index] = value;
    return 0x110;
}
