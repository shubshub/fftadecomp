#include "ffta.h"

/* 0x080CC9F0..0x080CCA20: 48 bytes, 23 instructions. */
extern const u8 *func_080CCCF0(u8 table);

u16 func_080CC9F0(u8 table, u8 index)
{
    const u8 *entries = func_080CCCF0(table);
    const u8 *entry;
    u32 low;

    if (!entries || !index) {
        return 0;
    }
    entry = entries + (index - 1) * 2;
    low = entry[4];
    return (entry[5] << 8) | low;
}
