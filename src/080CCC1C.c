#include "ffta.h"

extern u8 g_state_02000000[];

/* Complete [0x080CCC1C, 0x080CCC6A): 78 bytes, 36 instructions. */
u8 func_080CCC1C(void)
{
    u8 index;

    for (index = 0; index < 24; index++) {
        const u8 *entry = g_state_02000000 + index * 0x108;

        if (entry[0x84] != 0 && entry[0x170] == 0 &&
            (*(const u16 *)(entry + 0xA8) & 8))
            return 1;
    }
    return 0;
}
