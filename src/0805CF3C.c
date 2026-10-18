#include "ffta.h"

void func_0805CF3C(u8 first, u8 second, s16 *sum, s16 *difference)
{
    *sum = (first + second) * 16 - 38;
    *difference = (first - second) * 8 + 75;
}
