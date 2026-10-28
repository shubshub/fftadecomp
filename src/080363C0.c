#include "ffta.h"

extern u8 g_state_02000000[];

/* 080363C0..08036424: 100 bytes, 46 instructions. */
u8 func_080363C0(u8 identifier, const u8 *state)
{
    u8 index;

    if (!(g_state_02000000[0x2E58] & 1) && identifier == 9)
        return 0;
    if (!(g_state_02000000[0x2E58] & 2) && identifier == 0x1C)
        return 0;

    for (index = 0; index < 30; index++) {
        const u8 *entry = state + index * 12;

        if (entry[0xB3] == identifier)
            return index + 1;
    }
    return 0;
}
