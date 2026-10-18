#include "ffta.h"

void func_0801C960(s16 first, s16 second, s16 *firstOutput, s16 *secondOutput)
{
    s16 *origin = (s16 *)0x02007F40;

    *firstOutput = first - origin[0x12];
    *secondOutput = second - origin[0x13];
}
