#include "ffta.h"

void func_080CE420(void *object, u8 value)
{
    u8 *field = (u8 *)object + 0xD9;

    *field = value;
}
