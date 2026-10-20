#include "ffta.h"

void func_080BD11C(u8 value);
void func_080C95C0(u16 index, u32 value);

u32 func_08123900(void *context, const u8 *script)
{
    func_080BD11C(script[1]);
    func_080C95C0(0x35, script[1]);
    return 0x110;
}
