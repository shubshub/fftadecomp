/* func_0814862C - 0x0814862C, 16 bytes
 *
 * Sets a flag byte at +0x1c and returns the u16 at +0.  The load happens
 * first because the u16 comes back in r0 and the pointer then lives in r2 -
 * the argument is masked to u8 with lsl/lsr #24 before the store.
 */

#include "ffta.h"

u16 func_0814862C(Ent *p, u8 v) {
    u16 id = p->unknown_0;
    p->flag = v;
    return id;
}