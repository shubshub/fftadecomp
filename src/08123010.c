#include "ffta.h"

void func_08126DFC(void *context, u32 first, u32 second, u32 third);

u32 func_08123010(void *context, const u8 *script)
{
    func_08126DFC(context, script[1], script[2], script[3]);
    return 0x115;
}
