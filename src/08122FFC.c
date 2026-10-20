#include "ffta.h"

void func_08125760(u32 selector, u32 first, u32 second);

u32 func_08122FFC(void *context, const u8 *script)
{
    func_08125760(script[1], 0, 1);
    return 0x100;
}
