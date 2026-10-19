/* func_08013364 - 0x08013364, 26 bytes (22 code + 2 pad + 4 literal pool)
 *
 * Clears a byte flag at +0x26 of the global state object, but only once that
 * object exists.  The pointer lives at 0x0200918C - the same global
 * func_08013404 (src/20091/08013404.c) stores through - so the NULL test is
 * the object having been constructed.
 *
 *   00b5 0548 0068 0028 03d0 011c 2631 0020 0870 01bc 0047 c046
 *   pool 0x0801337C: 0x0200918C
 */

#include "ffta.h"

void func_08013364(void)
{
    u8 *state = *(u8 **)0x0200918C;

    if (state != 0) {
        state[0x26] = 0;
    }
}