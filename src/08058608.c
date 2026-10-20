#include "ffta.h"

u8 func_08058608(u32 value)
{
    u8 digits = 0;

    do {
        digits++;
        value /= 10;
    } while (value != 0);
    return digits;
}
