#include "ffta.h"

void *func_081255C8(u32 selector);

u32 func_08123080(void *context, const u8 *script)
{
    u8 *object = func_081255C8(script[1]);

    object[0x1F] = script[2];
    return 0x110;
}
