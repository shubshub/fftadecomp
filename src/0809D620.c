/* func_0809D620 - 0x0809D620, 24 bytes
 *
 * Writes five s16 fields.  The first argument value goes to two of them
 * (+0x1C and +0x1E) and the fifth one arrives on the stack.  The store order
 * is +0x1E, +0x20, +0x22, +0x24, then +0x1C last.
 */

#include "ffta.h"

void func_0809D620(Rec5 *rec, u16 a, u16 b, u16 c, u16 d) {
    rec->f2 = a;
    rec->f3 = b;
    rec->f4 = c;
    rec->f5 = d;
    rec->f1 = a;
}
