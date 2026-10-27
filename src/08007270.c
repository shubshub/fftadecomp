#include "ffta.h"

/* Complete [0x08007270, 0x0800749C): 556 bytes, 252 instructions. */
void func_08007270(s32 count, const double *knots, const double *values,
                   double *coefficients, double *workspace)
{
    double *widths;
    double *diagonal;
    s32 i;

    if (count <= 2) {
        for (;;)
            ;
    }

    widths = workspace;
    diagonal = workspace + count;
    coefficients[0] = 0.0;
    coefficients[count - 1] = 0.0;

    for (i = 0; i < count - 1; i++) {
        widths[i] = knots[i + 1] - knots[i];
        diagonal[i + 1] = (values[i + 1] - values[i]) / widths[i];
    }

    coefficients[1] = diagonal[2] - diagonal[1]
                      - widths[0] * coefficients[0];
    diagonal[1] = (knots[2] - knots[0]) * 2.0;

    for (i = 1; i < count - 2; i++) {
        double ratio = widths[i] / diagonal[i];

        coefficients[i + 1] = diagonal[i + 2] - diagonal[i + 1]
                              - coefficients[i] * ratio;
        diagonal[i + 1] = (knots[i + 2] - knots[i]) * 2.0
                          - widths[i] * ratio;
    }

    coefficients[count - 2] -= widths[count - 2] * coefficients[count - 1];
    for (i = count - 2; i > 0; i--)
        coefficients[i] = (coefficients[i] - widths[i] * coefficients[i + 1])
                          / diagonal[i];
}
