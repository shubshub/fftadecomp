/* func_080071A8 - 0x080071A8, 60 bytes (0x080071A8 .. 0x080071E4)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  70b5041c09040d0c2e1c00f017f80004000c854201d300200de02078022805d1201d
 *           690009180988401804e0201db10009180968401870bc02bc0847
 *
 * The function ends at the interworking return `pop {r1}; bx r1` on
 * 0x080071E0/0x080071E2; the next function (func_080071E4) starts at
 * 0x080071E4, so the indexed span is right.
 *
 * The object this walks has a header and a table of offsets:
 *   +0x00 u8    kind - 2 selects the narrow table
 *   +0x02 u16   count - read by func_080071E4 (`ldrh r0, [r0, #2]`)
 *   +0x04       the table itself
 * For kind == 2 the table entries are 16-bit offsets, otherwise they are
 * 32-bit ones.  The result is the table base plus the indexed offset, and
 * an out-of-range index gives 0.
 *
 * The count and the index are both u16, so the range test is unsigned
 * (`blo`), and the table base is recomputed in each arm.  The parameter is
 * used directly for the narrow table and through a widened copy for the
 * wide one, which is what puts the index in two registers.
 */

#include "ffta.h"

u16 func_080071E4(void *a);

u8 *func_080071A8(u8 *a, u16 b)
{
    u32 index = b;
    u32 count = func_080071E4(a);
    u8 *result;

    if (b >= count)
        return 0;
    if (a[0] == 2) {
        u8 *base = a + 4;
        result = base + *(u16 *)(base + b * 2);
    } else {
        u8 *base = a + 4;
        result = base + *(u32 *)(base + index * 4);
    }
    return result;
}
