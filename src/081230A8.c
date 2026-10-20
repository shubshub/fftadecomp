#include "ffta.h"

void func_08126B08(u32 first, u32 second, u32 third, u32 fourth);

u32 func_081230A8(void *context, const u8 *script)
{
    func_08126B08(script[1], script[2], script[3], script[4]);
    return 0x110;
}
