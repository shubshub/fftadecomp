#include "ffta.h"

/* Complete [0x08133BE0, 0x08133C00): 32 bytes, 16 instructions. */
u8 func_08133BE0(const u8 *flags, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;
    u8 value = flags[byte_index];
    if ((value >> bit_index) & 1)
        return 1;
    return 0;
}
