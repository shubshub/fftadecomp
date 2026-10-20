#include "ffta.h"

void func_08126E34(void *context, u32 first, u32 second);

u32 func_0812302C(void *context, const u8 *script)
{
    func_08126E34(context, script[1], script[2]);
    return 0x115;
}
