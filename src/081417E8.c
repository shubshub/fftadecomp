#include "ffta.h"

extern u16 func_0814180C(void);

u16 func_081417E8(void)
{
    if (!(u8)func_0814180C())
        return 0xFFFF;
    return *(const u16 *)0x020084D4;
}
