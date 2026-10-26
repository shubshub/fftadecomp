#include "ffta.h"

/* Complete target: [0x0806EFE4, 0x0806EFEE), 10 bytes, 5 instructions. */
u8 func_0806EFE4(const u8 *data)
{
    const u8 *entries = data + 1;
    return entries[data[0]];
}
