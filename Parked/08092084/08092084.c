/* func_08092084 - 0x08092084, 22 bytes
 *
 * Two bytes into a table at a signed 16-bit index.  Written as two indexed
 * stores rather than through a pointer: the compiler keeps the base in r4 and
 * recomputes the second address as (base + 1) + index * 2, which is what the
 * instructions do.  A single `p` pointer folds both addresses and loses that.
 *
 * The scale is index * 2, spelled (index << 16) >> 15 with an *arithmetic*
 * shift - a u16 index would give the logical shift instead.
 */

#include "ffta.h"

void func_08092084(u8 *base, s16 index, u8 lo, u8 hi) {
    base[index * 2] = lo;
    base[index * 2 + 1] = hi;
}
