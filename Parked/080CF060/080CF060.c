#include "ffta.h"

extern const u8 g_table_0855AE4C[][70];
extern u8 g_state_02000000[];

u32 func_080CF060(const void *record)
{
    const u8 *data = record;
    u32 result = 0;
    u32 identifier = data[0] | ((data[1] & 3) << 8);

    if ((g_table_0855AE4C[identifier][2] & 7) == 1) {
        const u8 *state = g_state_02000000;
        const u8 *selected = state + 0x2E34;
        s32 slot = 0;

        while ((selected[4] | ((selected[5] & 1) << 8)) !=
               (data[0] | ((data[1] & 3) << 8))) {
            slot++;
            if (slot == 5)
                break;
            selected += 6;
        }
        if ((selected[2] & 31) == state[0x1F69])
            result = 1;
    }
    return result;
}
