#include "ffta.h"

void func_081257D0(u8 column, u8 row, u8 value);

u32 func_08123564(void *context, const u8 *script)
{
    func_081257D0(script[1] & 0xF, script[1] >> 4, script[2]);
    return 0x110;
}
