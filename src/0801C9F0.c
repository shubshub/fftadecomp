#include "ffta.h"

void func_0801C9F0(s16 first, s16 second, s16 third,
                   s16 *firstOutput, s16 *secondOutput, s16 *thirdOutput)
{
    *firstOutput = first >> 5;
    *secondOutput = second >> 4;
    *thirdOutput = third >> 5;
}
