#include "ffta.h"

void func_080C9574(u32 value, u32 option);

u32 func_08122E90(void *context, const u8 *script)
{
    func_080C9574(script[1] | (script[2] << 8), script[3]);
    return 0x110;
}
