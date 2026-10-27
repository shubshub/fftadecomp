#include "ffta.h"

extern u8 func_080CD98C(void *unit);
extern u8 func_080CDB54(void *unit);

s32 func_0812C634(void *first, void *second)
{
    s32 adjustment = 0;

    if (func_080CD98C(second) != 0)
        adjustment -= 20;
    if (func_080CDB54(second) != 0)
        adjustment -= 10;
    if (func_080CD98C(first) != 0)
        adjustment += 50;
    return adjustment;
}
