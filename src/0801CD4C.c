/* func_0801CD4C - 0x0801CD4C, 26 bytes + 4-byte literal pool
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  30b5 064d 6c7b 0470 e87b 0870 a87a 1070 287b 1870 30bc 01bc 0047
 *   pool    02007f10
 *
 * Scatters four bytes out of a fixed-address table at 0x02007F10 (top of the
 * 32 KiB EWRAM mirror).  The ROM loads that address once into r5 and indexes
 * off it, so the address has to live in a *variable*:
 *
 *   - writing ((u8 *)0x02007F10)[0x0d] directly makes the compiler constant
 *     fold each byte into its own absolute address, and Thumb-1 can only
 *     reach those through a literal pool per access - four pool loads, no
 *     shared register, wrong bytes entirely;
 *   - `u8 *t = (u8 *)0x02007F10;` keeps one load and matches exactly.
 *
 * Two more build notes: agbcc's cc1 does not run the preprocessor (macros
 * and comments must be handled by `cpp` first), and it targets Thumb/elf by
 * default, so the mode flag is -mthumb-interwork.
 */

#include "ffta.h"

void func_0801CD4C(u8 *a, u8 *b, u8 *c, u8 *d) {
    u8 *t = (u8 *)0x02007F10;
    *a = t[0x0d];
    *b = t[0x0f];
    *c = t[0x0a];
    *d = t[0x0c];
}