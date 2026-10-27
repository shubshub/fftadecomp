#include "ffta.h"

/* 08002B28..08002B4C: 36 bytes, 18 instructions. */
u8 func_08002B28(u8 character)
{
    if (character == ' ' || character == '\t' || character == '\r' ||
        character == '\n' || character == '\f')
        return 1;
    return 0;
}
