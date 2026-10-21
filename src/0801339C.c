/* func_0801339C - 0x0801339C, 20 bytes (16 code + 4 literal pool)
 *
 * Sets bit 0 of the halfword at +0x20 of the global state object.  The object
 * pointer lives at 0x0200918C - the same global func_08013364
 * (src/08013364.c) and func_08013404 (src/20091/08013404.c) work through.
 *
 *   0004 000c 0249 0a68 0121 0843 1084 7047
 *   pool 0x080133AC: 0x0200918C
 */

#include "ffta.h"

void func_0801339C(u16 value)
{
    u16 *state = *(u16 **)0x0200918C;

    state[0x10] = value | 1;
}
