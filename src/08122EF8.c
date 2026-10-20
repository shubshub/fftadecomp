#include "ffta.h"

extern u8 g_state_02000000[];

u32 func_08122EF8(void *context, const u8 *script)
{
    g_state_02000000[0x2190] = script[1];
    g_state_02000000[0x2191] = script[1];
    return 0x110;
}
