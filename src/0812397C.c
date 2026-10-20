#include "ffta.h"

void func_08124FD0(u16 index);

u32 func_0812397C(void *context, const u8 *script)
{
    func_08124FD0(script[1] - 1);
    return 0x110;
}
