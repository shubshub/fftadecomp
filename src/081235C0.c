#include "ffta.h"

void func_08123E00(u8 selector);
u8 func_080C95A8(u16 index);

u32 func_081235C0(void *context, const u8 *script)
{
    func_08123E00(script[1]);
    return func_080C95A8(13) == 1 ? 0x119 : 0x110;
}
