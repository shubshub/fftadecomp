/* func_0801E6F0 - 0x0801E6F0, 16 bytes (12 of code + one 4-byte literal pool)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  024b 9a8c 0280 d88c 0880 7047 7f40 0002
 *   pool    02007f40
 *
 * Reads the two halfwords at +0x24 and +0x26 of the state block at
 * 0x02007F40 and writes them through the two out-pointers.  Every caller
 * passes a stack slot and reads it back with `ldrh`, so the destinations
 * are 16-bit.
 *
 * The state block address lives in a local pointer: written inline the
 * compiler folds each access into its own absolute address and needs a
 * literal pool entry per access, while the ROM has one pool word and one
 * base register with the two offsets folded into the `ldrh` immediates.
 */

#include "ffta.h"

void func_0801E6F0(u16 *first, u16 *second) {
    u16 *source = (u16 *)0x02007F40;

    *first = source[18];
    *second = source[19];
}
