#include "ffta.h"

extern u32 func_08142B28(u32 value, u32 divisor);

/* Complete [0x08013BC0, 0x08013BEC): 44 bytes, 21 instructions. */
u16 func_08013BC0(u16 value, u16 multiple)
{
    u16 remainder = func_08142B28(value, multiple);
    u16 result;

    if (remainder != 0)
        result = value + multiple - remainder;
    else
        result = value;
    return result;
}
