#include "ffta.h"

u32 func_080C8570(u8 first, u8 second, u8 selector);

u32 func_080C92F0(void *data, u32 selector)
{
    u8 *object = data;
    u8 selected = selector;

    if (selected == 0 && object[0x100] != 0)
        return object[0x100];
    return func_080C8570(object[5], object[7], selected);
}
