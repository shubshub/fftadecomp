#include "ffta.h"

struct State08050CA4 {
    u8 unknown_0000[0x1F3C];
    u16 entries[20];
};

extern struct State08050CA4 g_state_02000000;

/* Complete target: [0x08050CA4, 0x08050CDC), 56 bytes. */
u32 func_08050CA4(u32 *destination)
{
    u32 count = 0;
    u32 state_address = (u32)&g_state_02000000;
    const u16 *entry = (const u16 *)(state_address + 0x1F3C);
    u32 *output = destination;
    s32 remaining;

    for (remaining = 19; remaining >= 0; remaining--) {
        if (*entry != 0) {
            if (destination != 0)
                *output = *entry;
            output++;
            count++;
        }
        entry++;
    }
    return count;
}
