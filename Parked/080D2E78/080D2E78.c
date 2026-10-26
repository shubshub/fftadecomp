#include "ffta.h"

/* 0x080D2E78..0x080D2EB2: 58 bytes, 27 instructions. */
extern const u8 g_table_0855AE4C[];

u32 func_080D2E78(const u8 *descriptor)
{
    u32 low = descriptor[0];
    u32 high = descriptor[1];
    u32 id = ((high & 3) << 8) | low;
    const u8 *record = g_table_0855AE4C + id * 0x46;
    u32 flags_low = record[0x41];
    u32 flags = (record[0x42] << 8) + flags_low;

    if (!(flags & 4)) {
        return 0;
    }
    return 1;
}
