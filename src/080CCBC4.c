#include "ffta.h"

extern u8 g_state_02000000[];

/* Complete target [0x080CCBC4, 0x080CCBFC): 56 bytes, 23 instructions. */
u8 func_080CCBC4(void)
{
    u8 index = 0;
    u8 count = 0;

    for (; index < 20; index++) {
        const u8 *record = &g_state_02000000[index * 16];

        if (*(const u32 *)(record + 0x2E78) != 0)
            count++;
    }
    return count;
}
