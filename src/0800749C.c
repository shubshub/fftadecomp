#include "ffta.h"

/* Complete [0x0800749C, 0x080075CC): 304 bytes, 130 instructions. */
double func_0800749C(double position, s32 count, const double *knots,
                     const double *values, const double *coefficients)
{
    s32 lower = 0;
    s32 upper = count - 1;

    while (lower < upper) {
        s32 middle = (lower + upper) / 2;

        if (knots[middle] < position)
            lower = middle + 1;
        else
            upper = middle;
    }
    if (lower > 0)
        lower--;

    {
        double width = knots[lower + 1] - knots[lower];
        double offset = position - knots[lower];
        double next_coefficient = coefficients[lower + 1];
        double coefficient = coefficients[lower];
        return (((next_coefficient - coefficient) * offset / width
                 + 3.0 * coefficient) * offset
                + ((values[lower + 1] - values[lower]) / width
                   - (coefficient + coefficient + next_coefficient) * width))
               * offset + values[lower];
    }
}
