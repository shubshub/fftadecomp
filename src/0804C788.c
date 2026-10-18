/* func_0804C788 - 0x0804C788, 24 bytes
 *
 * Two bytes at +0x10 of a 28-byte record.  The scale is written as an
 * explicit offset first and the base added to it afterwards, because the
 * instructions compute index * 28 in r4 and then add the base into r4 - the
 * reverse of folding the base into the accumulator.
 */

#include "ffta.h"

void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi) {
    u32 off = index * 28;
    base[off + 0x10] = lo;
    base[off + 0x11] = hi;
}
