#include "ffta.h"

typedef signed long long s64;

/* Complete [0x08008480, 0x080086CE): 590 bytes, 287 instructions.
 * The 16.16 fixed-point twin of func_08007270 (src/08007270.c): the same
 * natural cubic spline setup, on s64 instead of double.  The s64 products
 * and quotients are the runtime calls __muldi3 (func_08142A20) and
 * __divdi3 (func_08142280). */
void func_08008480(s32 count, const s64 *knots, const s64 *values,
                   s64 *coefficients, s64 *workspace)
{
    s64 *widths;
    s64 *diagonal;
    s32 i;

    if (count <= 2) {
        for (;;)
            ;
    }

    widths = workspace;
    diagonal = workspace + count;
    coefficients[0] = 0;
    coefficients[count - 1] = 0;

    for (i = 0; i < count - 1; i++) {
        widths[i] = knots[i + 1] - knots[i];
        diagonal[i + 1] = ((values[i + 1] - values[i]) << 16) / widths[i];
    }

    /* coefficients[0] and coefficients[count - 1] were just zeroed, but the
     * ROM reloads them and forms both boundary products (__muldi3 at
     * 0x08008534 and 0x08008642), as func_08007270 does with doubles. */
    coefficients[1] = diagonal[2] - diagonal[1]
                      - (widths[0] * coefficients[0] >> 16);
    diagonal[1] = (knots[2] - knots[0]) << 1;

    for (i = 1; i < count - 2; i++) {
        s64 ratio = (widths[i] << 16) / diagonal[i];

        coefficients[i + 1] = diagonal[i + 2] - diagonal[i + 1]
                              - (coefficients[i] * ratio >> 16);
        diagonal[i + 1] = ((knots[i + 2] - knots[i]) << 1)
                          - (widths[i] * ratio >> 16);
    }

    coefficients[count - 2] -= widths[count - 2] * coefficients[count - 1] >> 16;
    for (i = count - 2; i > 0; i--)
        coefficients[i] = ((coefficients[i] - (widths[i] * coefficients[i + 1] >> 16))
                           << 16) / diagonal[i];
}
