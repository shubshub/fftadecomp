#include "ffta.h"

typedef signed long long s64;

/* Complete [0x080086D0, 0x08008818): 328 bytes, 158 instructions.
 * The 16.16 fixed-point twin of func_0800749C (src/0800749C.c): the same
 * binary search and cubic Hermite evaluation, on s64 instead of double. */
s64 func_080086D0(s64 position, s32 count, const s64 *knots,
                  const s64 *values, const s64 *coefficients)
{
    s32 lower = 0;
    s32 upper = count - 1;

    while (lower < upper) {
        s32 middle = (lower + upper) >> 1;

        if (knots[middle] < position)
            lower = middle + 1;
        else
            upper = middle;
    }
    if (lower > 0)
        lower--;

    {
        s64 offset;
        s64 width;
        s64 coefficient;
        s64 next_coefficient;
        s64 value;
        s64 next_value;

        width = knots[lower + 1] - knots[lower];
        offset = position - knots[lower];
        coefficient = coefficients[lower];
        next_coefficient = coefficients[lower + 1];
        value = values[lower];
        next_value = values[lower + 1];

        /* The ROM forms coefficient + coefficient once (adds/adcs at
         * 0x0800877C) and adds coefficient to it at 0x08008784 and
         * next_coefficient at 0x080087D0. */
        return ((((((((next_coefficient - coefficient) * offset >> 16) << 16) / width
                    + (coefficient + coefficient + coefficient)) * offset) >> 16)
                 + (((next_value - value) << 16) / width
                    - ((coefficient + coefficient + next_coefficient) * width >> 16)))
                * offset >> 16) + value;
    }
}
