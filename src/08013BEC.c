#include "ffta.h"

/* Complete [0x08013BEC, 0x08013C1E): 50 bytes, 25 instructions. */
u32 func_08013BEC(u8 value)
{
    u32 result = 0;

    if (value == 0x80 || value == 0x87 || value == 0x13 ||
        value == 0x89 || value == 0x55 || value == 0x56 ||
        (u8)(value - 0x90) <= 0x1C)
        result = 1;

    return result;
}
