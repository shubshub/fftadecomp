/* func_080CDB24 - 0x080CDB24, 24 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5 eb30 0421 0078 0840 0028 01d0 0120 00e0 0020 02bc 0847
 *
 * Tests bit 2 of the flag byte at +0xEB of an object and returns it as a
 * boolean.  The epilogue pops the return address into r1 and branches through
 * it: a Thumb interworking return.
 */

#include "ffta.h"

u8 func_080CDB24(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEB;
    u8 mask = 4;

    if (!(*flags & mask))
        return 0;
    return 1;
}
