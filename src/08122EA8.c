#include "ffta.h"

void func_080C95C0(u16 index, u32 value);

u32 func_08122EA8(void *context, const u8 *script)
{
    func_080C95C0(script[1] | (script[2] << 8), script[3]);
    return 0x110;
}
