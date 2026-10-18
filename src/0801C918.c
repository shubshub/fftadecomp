#include "ffta.h"

void func_0801C918(s16 first, s16 second, s16 third, s16 *first_output,
                   s16 *second_output, s16 *third_output)
{
    s16 *origin;

    *first_output = (first - third) >> 1;
    origin = (s16 *)0x02007F40;
    *first_output += origin[0x10];
    *second_output = ((first + third) >> 2) - (second >> 1);
    *second_output += origin[0x11];
    *third_output = first + third;
}
