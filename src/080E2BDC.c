#include "ffta.h"

extern u16 func_08005BAC(void *object);

u8 func_080E2BDC(void *object)
{
    u16 state = func_08005BAC(object);

    if (state > 0x101 || state == 2)
        return 1;
    return 0;
}
