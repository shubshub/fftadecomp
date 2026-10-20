#include "ffta.h"

void func_08124DF0(u16 index, u8 selector);

u32 func_081235A8(void *context, const u8 *script)
{
    func_08124DF0(script[1] | (script[2] << 8), script[3]);
    return 0x110;
}
