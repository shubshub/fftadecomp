#include "ffta.h"

void func_08127AF8(void *context, u32 selector, u32 start, u32 count,
                   u32 amount, u32 mode);

u32 func_0812352C(void *context, const u8 *script)
{
    s8 start = script[2] & 0x0F;

    func_08127AF8(context, script[1], (u8)start,
                  (u8)((script[2] >> 4) - start + 1), script[3], 0);
    return 0x115;
}
