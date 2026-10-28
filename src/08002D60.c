#include "ffta.h"

/* 0x08002D60..0x08002D82: 34 bytes / 17 instructions. */
u8 func_08002D60(u8 character)
{
    if ((u8)(character - 'A') <= 'Z' - 'A')
        return character + ('a' - 'A');
    return character;
}
