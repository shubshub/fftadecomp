#include "ffta.h"

u8 func_080C8240(void *object);
u32 func_080CB65C(void *object, u32 selector);
u32 func_080CB714(void *object);

u16 func_08022238(void *object, u8 *output)
{
    if (func_080C8240(object))
        *output = func_080CB65C(object, 0);
    else
        *output = func_080CB65C(object, 1);
    return func_080CB714(object);
}
