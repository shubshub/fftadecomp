/* func_08017514 - 0x08017514, 18 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 029c 0170 4270 8370 c470 10bc 01bc 0047
 *
 * Writes four bytes to consecutive addresses.  r0=p, r1..r3 carry three of
 * them and the fourth arrives on the stack - which is the only reason r4 is
 * saved.  The epilogue pops the return address into r0 and branches through
 * it: a Thumb interworking return, so an ARM caller gets its ARM state back.
 *
 * This was the project's first match; it is what identified the compiler.
 */

#include "ffta.h"

void func_08017514(u8 *p, u8 a, u8 b, u8 c, u8 d) {
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
}