#include "ffta.h"

/* Complete [0x0801843C, 0x08018470): 52 bytes, 26 instructions. */
u8 func_0801843C(u8 code)
{
    u8 special = 0;

    if (code == 3 || code == 4 || code == 10 || code == 11 ||
        code == 12 || code == 13 || code == 15 || code == 14)
        special = 1;
    return special;
}
