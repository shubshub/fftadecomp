#include "ffta.h"

void func_08127AF8(void *context, u32 selector, u32 value, u32 enabled,
                   u32 mode, u32 duration);

u32 func_081234FC(void *context, const u8 *script)
{
    func_08127AF8(context, script[1], script[2] & 0x0F, 1,
                  (script[2] & 0x70) >> 4, script[3]);
    return 0x115;
}
