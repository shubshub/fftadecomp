#include "ffta.h"

u32 func_08002AC8(u8 character)
{
    if ((u8)(character - ' ') <= '~' - ' ')
        return 1;
    return 0;
}
