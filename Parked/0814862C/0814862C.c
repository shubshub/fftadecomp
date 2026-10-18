/* func_0814862C - 0x0814862C, 16 bytes
 *
 * Sets a byte at +0x1C from the second argument, truncated to u8, after
 * testing the u16 at +0.  The test does not change what is stored - both
 * sides store the same byte - so none of it reaches the ROM: the 16 bytes
 * are the id load, the store, and the u8 truncation the compiler had already
 * put in r1.  The frame the test asked for is still there, because agbcc
 * decides the frame before the branch is threaded away, which is why this
 * leaf does push {lr} ... pop {r0} and returns nothing: pop {r0} is the void
 * return path, a function returning a value would pop {r1} here.
 *
 * The offsets come from the instructions.  What the members mean is not
 * identified, so the bytes in front of them are named unknown_*.
 */

#include "ffta.h"

typedef struct {
    u16 id;                 /* +0x00, loaded but not used for anything */
    u8  unknown_02[0x1a];   /* +0x02 .. +0x1B */
    u8  flag;               /* +0x1C */
} Struct0814862C;

void func_0814862C(Struct0814862C *p, u32 v) {
    u8 b = (u8)v;
    if (p->id)
        p->flag = b;
    else
        p->flag = b;
}