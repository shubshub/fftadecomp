#include "ffta.h"

void func_0812C4E4(void *context, const u8 *script);

u32 func_08123A60(void *context, const u8 *script)
{
    func_0812C4E4(context, script);
    return script[8] ? 0x115 : 0x110;
}
