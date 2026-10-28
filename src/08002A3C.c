#include "ffta.h"

/* 08002A3C..08002A64: 40 bytes. */
u8 func_08002A3C(u8 character)
{
    if ((u8)(character - 'a') < 26 || (u8)(character - 'A') < 26)
        return 1;
    return 0;
}
