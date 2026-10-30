#include "ffta.h"

/* 0x080CB53C..0x080CB54C:
 * 00 04 02 49 40 18 00 0C 70 47 00 00 00 00 39 04. */
u16 func_080CB53C(u16 value)
{
    return value + 0x439;
}
