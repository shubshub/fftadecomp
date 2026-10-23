#include "ffta.h"

/* 0x08002B4C-0x08002B66: 26 bytes; external alignment is excluded. */
u8 func_08002B4C(u8 character)
{
    if (character >= 'A' && character <= 'Z')
        return 1;

    return 0;
}
