#include "ffta.h"

extern u8 g_state_02002E34[][6];

u32 func_08036440(u8 value, u32 mode);

void func_080CF690(void)
{
    s32 active = 0;
    s32 slot;

    for (slot = 0; slot < 5; slot++) {
        u8 *record = g_state_02002E34[slot];

        if (record[0] & 7) {
            if ((record[1] & 0x80) &&
                !func_08036440(record[2] & 31, 0)) {
                record[1] &= 0x7F;
                break;
            }
            if (record[0] & 7)
                active++;
        }
    }
    for (slot = 0; slot < 5; slot++) {
        u8 *record = g_state_02002E34[slot];

        if (record[0] & 7) {
            u8 flags = record[2];

            if (!(flags & 0x20) && !(record[1] & 0x80)) {
                u8 counter = record[5];

                if (counter & 0xFE) {
                    if ((counter & 0xFE) != 0xF0)
                        record[5] = (counter & 1) | (((counter >> 1) - 1) << 1);
                    if (record[5] & 0xFE)
                        continue;
                }
                record[2] = (flags | 0x40) & ~0x20;
                active = 0;
            }
        }
    }
    if (active == 5) {
        s32 minimum = 7;
        s32 selected = -1;

        for (slot = 0; slot < 5; slot++) {
            u8 *record = g_state_02002E34[slot];

            if (record[2] & 0x40) {
                selected = -1;
                break;
            }
            if ((record[0] & 7) && !(record[1] & 0x80) &&
                !(record[0] & 0x30)) {
                u8 counter = record[5] >> 1;

                if (counter < minimum) {
                    minimum = counter;
                    selected = slot;
                }
            }
        }
        if (selected != -1)
            g_state_02002E34[selected][2] |= 0x40;
    }
}
