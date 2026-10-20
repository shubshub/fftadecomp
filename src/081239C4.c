#include "ffta.h"

void func_0812B7D0(void *context, u16 value);

u32 func_081239C4(void *context, const u8 *script)
{
    func_0812B7D0(context, script[1] | (script[2] << 8));
    return 0x110;
}
