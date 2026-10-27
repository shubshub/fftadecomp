#include "ffta.h"

extern u8 func_080CD50C(void *unit);

s32 func_0812C610(void *unit)
{
    u8 code = func_080CD50C(unit);

    if (code == 13)
        return -50;
    if (code == 4)
        return -15;
    return 0;
}
