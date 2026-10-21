/* func_080CDA4C - 0x080CDA4C, 24 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5 ec30 0221 0078 0840 0028 01d0 0120 00e0 0020 02bc 0847
 *
 * Tests bit 1 of the flag byte at +0xEC of an object and returns it as a
 * boolean.  The epilogue pops the return address into r0 and branches through
 * it: a Thumb interworking return.
 */

#include "ffta.h"

u8 func_080CDA4C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEC;
    u8 mask = 2;

    if (!(*flags & mask))
        return 0;
    return 1;
}
