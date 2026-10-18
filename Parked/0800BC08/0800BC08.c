/* func_0800BC08 - 0x0800BC08, 26 bytes
 *
 * Writes two s16 into a 40-byte record of the table at 0x02009000, selected by
 * an index the code masks to a byte (lsl/lsr #24) before scaling by 40 - the
 * same shift/subtract/shift shape as func_0804C788.  The table address is a
 * constant loaded through a literal pool, held in a local so the three stores
 * share one base.
 *
 *   target  10b5 0006 000e 054c 8300 1b18 db00 1b19 1983 5a83 10bc 01bc 0047
 */

#include "ffta.h"

void func_0800BC08(u32 index, s16 a, s16 b) {
    Rec40 *r = (Rec40 *)((u8 *)0x02009000 + (u8)index * 40);
    r->x = a;
    r->y = b;
}
