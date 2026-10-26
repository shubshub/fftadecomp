#include "ffta.h"

extern u16 data_02001F30[];

/* Complete [0x080CC7CC, 0x080CC7F8): 44 bytes, 20 instructions. */
u32 func_080CC7CC(void)
{
    u8 index = 0;
    u8 count = 0;
    const u16 *table = data_02001F30;

    for (; index < 5; index++) {
        if (table[index] != 0)
            count++;
    }
    return count;
}
