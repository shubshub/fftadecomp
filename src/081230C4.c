#include "ffta.h"

void func_08126B3C(u32 first, u32 second, u32 third);

u32 func_081230C4(void *context, const u8 *script)
{
    func_08126B3C(script[1], script[2], script[3]);
    return 0x110;
}
