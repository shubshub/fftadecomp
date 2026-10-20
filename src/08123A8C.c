#include "ffta.h"

void *func_08125578(u32 selector);
u8 func_080C8260(void *object);
u8 func_080C8240(void *object);

u32 func_08123A8C(u16 *context, const u8 *script)
{
    void *object = func_08125578(script[1]);

    if (object != 0 && !func_080C8260(object) && !func_080C8240(object))
        *context += script[2] | (script[3] << 8);
    return 0x110;
}
