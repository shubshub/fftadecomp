#include "ffta.h"

/* 0x08002AAC-0x08002AC6: 26 bytes; external alignment is excluded. */
u32 func_08002AAC(u8 character)
{
    if ((u8)(character - 'a') <= 'z' - 'a')
        return 1;
    return 0;
}
