#include "ffta.h"

/* 0x0812C670..0x0812C684: 20 bytes. */
int func_0812C670(int value)
{
    if (value < 5)
        value = 5;
    else if (value >= 95)
        value = 95;
    return value;
}
