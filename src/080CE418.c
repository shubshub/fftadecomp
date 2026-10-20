#include "ffta.h"

void func_080CE418(void *object, u8 value)
{
    u8 *data = object;

    data[0xD8] = value;
}
