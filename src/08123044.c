#include "ffta.h"

void func_08126EA4(void *context, u32 first, u32 value, u32 third);

u32 func_08123044(void *context, const u8 *script)
{
    func_08126EA4(context, script[1], script[2] | (script[3] << 8), script[4]);
    return 0x115;
}
