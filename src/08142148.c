#include "ffta.h"

/* Complete [0x08142148,0x08142160), 24 bytes, 9 reached instructions.
 * The copied scan returns the remaining byte count from the first non-FF byte. */
u32 func_08142148(const u8 *bytes, u32 (*scan)(const u8 *))
{
    if (scan(bytes))
        return 0x8004;
    return 0;
}
