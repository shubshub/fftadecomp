#include "ffta.h"

/* Target: complete [0x081493AC, 0x081493C0), 20 bytes, 10 instructions.
 * Table entries have a seven-byte stride and a byte value at +4. */
u8 func_081493AC(const u8 *entries, u8 column, u8 row)
{
    u32 index = (row << 4) + column;

    entries += index * 7;
    return entries[4];
}
