#include "ffta.h"

/* Complete [0x08002A08, 0x08002A3C): 52 bytes, 26 instructions. */
u8 func_08002A08(u8 character)
{
    if ((u8)(character - 'a') < 26 ||
        (u8)(character - 'A') < 26 ||
        (u8)(character - '0') < 10)
        return 1;
    return 0;
}
