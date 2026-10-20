#include "ffta.h"

extern u8 g_state_02000000[];

u8 func_08036330(u8 selector);
void func_08036584(u32 selector);

u32 func_08122F24(void *context, const u8 *script)
{
    g_state_02000000[0x1F69] = func_08036330(script[1]);
    g_state_02000000[0x3C2B] = 0;
    func_08036584(g_state_02000000[0x1F69]);
    return 0x110;
}
