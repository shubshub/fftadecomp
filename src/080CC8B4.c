#include "ffta.h"

/* Complete [0x080CC8B4, 0x080CC8D0): 28 bytes, 14 instructions. */
u8 func_080CC8B4(u16 value)
{
    if (value < 10)
        return 0;
    if (value < 20)
        return 1;
    return 2;
}
