#include "ffta.h"

void func_081286DC(void *context, u8 value);

u32 func_08123834(void *context, const u8 *script)
{
    func_081286DC(context, script[1]);
    return 0x115;
}
