#include "ffta.h"

/* Target: [0x08149194, 0x081491C0), 44 bytes, 22 instructions. */
void func_08149194(u8 entries[][7], u8 column, u8 row, s32 enabled)
{
    u8 *entry = entries[row * 16 + column];
    u32 flags;

    if (enabled)
        flags = entry[1] | 0x40;
    else
        flags = entry[1] & ~0x40;
    entry[1] = flags;
}
