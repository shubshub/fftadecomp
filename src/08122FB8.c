#include "ffta.h"

void func_08124560(u32 first, u32 second);

u32 func_08122FB8(void *context, const u8 *script)
{
    func_08124560(script[1], script[2]);
    return 0x110;
}
