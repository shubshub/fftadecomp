#include "ffta.h"

/* Complete [0x080258C4, 0x080258F8): 52 bytes, 25 instructions.
 * Target: 10b50c04240ca7f01ffe0006000e0a2808d101202040002802d0601c0004040c
 * 640803e0042801d16004040c201c10bc02bc0847
 *
 * Scales `value` by the code func_080CD50C returns for the unit: 10 halves
 * it rounding up, 4 doubles it, anything else returns it unchanged.  The
 * arithmetic is 16-bit throughout.
 */
extern u8 func_080CD50C(const void *unit);

u16 func_080258C4(const void *unit, u16 value)
{
    u8 category = func_080CD50C(unit);
    u16 result = value;

    if (category == 10) {
        if (result & 1)
            result++;
        result >>= 1;
    } else if (category == 4) {
        result *= 2;
    }
    return result;
}
