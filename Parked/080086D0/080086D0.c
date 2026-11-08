#include "ffta.h"

typedef long long s64;


/* Target: 0x080086D0-0x08008818, 328 bytes. */
s64 func_080086D0(s64 x, s32 count, s64 *knots, s64 *values, s64 *slopes)
{
    s32 lo, hi, mid;
    s64 dx, h, a0, a1, b0, b1, t, u, w, a2;

    lo = 0;
    hi = count - 1;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        if (x > knots[mid])
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo > 0)
        lo--;

    h = knots[lo + 1] - knots[lo];
    dx = x - knots[lo];
    a0 = slopes[lo];
    a1 = slopes[lo + 1];
    b0 = values[lo];
    b1 = values[lo + 1];

    t = (((a1 - a0) * dx >> 16) << 16) / h;
    a2 = a0 + a0;
    u = (a0 + a2 + t) * dx >> 16;
    w = ((b1 - b0) << 16) / h;
    w -= (a2 + a1) * h >> 16;
    return ((u + w) * dx >> 16) + b0;
}
