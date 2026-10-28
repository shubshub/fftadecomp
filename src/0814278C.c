/* 0x0814278C..0x08142862: 214 bytes. */
#include "ffta.h"

typedef signed long long s64;
typedef unsigned long long u64;

s64 func_0814278C(double value)
{
    double high;
    u64 result;

    if (value < 0)
        return 0;

    high = value / ((u64)1 << 32);
    result = (u32)high;
    result <<= 32;
    value -= (double)result;

    if (value < 0)
        result -= (u32)(-value);
    else
        result += (u32)value;
    return result;
}
