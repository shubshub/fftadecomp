#include "ffta.h"

/* 0x080CCB94..0x080CCBC4: 48 bytes. */
extern u8 g_state_02000000[];

u8 func_080CCB94(void)
{
    u8 i;

    for (i = 0; i < 20; i++) {
        const u8 *record = &g_state_02000000[i * 16];

        if (*(const u32 *)(record + 0x2E78) != 0)
            return 1;
    }
    return 0;
}
