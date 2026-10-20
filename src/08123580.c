#include "ffta.h"

void func_08127B40(void *context, u32 selector, u32 value,
                  u32 low_nibble, u32 high_nibble);

u32 func_08123580(void *context, const u8 *script)
{
    func_08127B40(context, script[1], script[2], script[4] & 15,
                  script[4] >> 4);
    return 0x115;
}
