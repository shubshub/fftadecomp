#include "ffta.h"

/* 0x08131030..0x0813103E: 14 bytes, 6 instructions. */
extern u32 func_081308F4(u32 unit);

u8 func_08131030(u32 unit)
{
    return func_081308F4(unit);
}
