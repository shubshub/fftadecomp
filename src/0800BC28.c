/* func_0800BC28 - 0x0800BC28, 30 bytes
 *
 * Reads the same pair back out of the 40-byte records at 0x02009000 that
 * func_0800BC08 writes: same byte mask, same index * 40 scale, same pooled
 * base.
 *
 *   target  10b5 0006 000e 064c 8300 1b18 db00 1b19 188b 0880 588b 1080
 *           10bc 01bc 0047
 */

#include "ffta.h"

void func_0800BC28(u32 index, s16 *a, s16 *b) {
    Rec40 *r = (Rec40 *)((u8 *)0x02009000 + (u8)index * 40);
    *a = r->x;
    *b = r->y;
}
