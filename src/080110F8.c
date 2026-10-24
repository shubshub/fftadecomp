/* 0x080110F8: 6 bytes, complete body ends at 0x080110FE. */
#include "ffta.h"

void func_080110F8(u8 *object, u8 value)
{
    object[0x24] = value;
}
