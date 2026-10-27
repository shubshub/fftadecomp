#include "ffta.h"

extern u8 func_080CD8CC(void *unit);

u8 func_0812F17C(void *unit)
{
    if (func_080CD8CC(unit) != 0)
        return 1;
    return 0;
}
