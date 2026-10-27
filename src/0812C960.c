#include "ffta.h"

extern u32 func_080C92F0(void *object, u32 selector);

u8 func_0812C960(void *object)
{
    if (!(func_080C92F0(object, 0x16) & 0x80))
        return 0;
    return 1;
}
