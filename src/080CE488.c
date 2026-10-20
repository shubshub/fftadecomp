#include "ffta.h"

void func_080CE488(void *object, u8 value)
{
    u8 *field = (u8 *)object + 0xE6;

    *field = value;
}
