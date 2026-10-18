#include "ffta.h"

void func_0801CA78(s16 first, s16 second, s16 third,
                   s16 *firstOutput, s16 *secondOutput, s16 *thirdOutput)
{
    *firstOutput = first * 32 + 16;
    *secondOutput = second * 16;
    *thirdOutput = third * 32 + 16;
}
