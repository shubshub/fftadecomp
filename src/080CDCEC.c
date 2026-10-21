// 0x080CDCEC - 24 bytes.
//
// Reads bit 6 of the flag byte at +0xED of the object and answers 0 or 1.
// The same shape as the other flag getters in this family (0x080CD8B4,
// 0x080CD8CC, 0x080CDAAC, 0x080CDAC4) with a different byte and mask.
#include "ffta.h"

u8 func_080CDCEC(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xED;
    u8 mask = 0x40;

    if (!(*flags & mask))
        return 0;
    return 1;
}
