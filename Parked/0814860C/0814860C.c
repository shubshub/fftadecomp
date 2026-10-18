/* func_0814860C - 0x0814860C, 32 bytes
 *
 * Rewrites the block that starts at +0xC and returns the id at +0, read last
 * because the return statement is the last thing evaluated.  The compiler
 * materialises the block pointer once (base + 0xC) and offsets into it; the
 * two cleared u16 fields go first, then the u32, then the tail.
 */

#include "ffta.h"

u16 func_0814860C(Hdr *h, u32 value, u16 tail) {
    HdrTail *t = &h->tail_block;
    t->cleared_a = 0;
    t->cleared_b = 0;
    t->value = value;
    t->tail = tail;
    return h->id;
}
