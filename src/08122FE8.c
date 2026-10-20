#include "ffta.h"

void func_08125760(u32 selector, u32 first, u32 second);

u32 func_08122FE8(void *context, const u8 *script)
{
    func_08125760(script[1], 1, 0);
    return 0x100;
}
