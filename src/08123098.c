#include "ffta.h"

void func_08124D58(u32 selector);

u32 func_08123098(void *context, const u8 *script)
{
    func_08124D58(script[1]);
    return 0x110;
}
