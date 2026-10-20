#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 statistics[9][2];
    u8 selection;
} SelectionStats;

extern const u8 g_table_08528556[][16];
extern SelectionStats g_state_020021A0;
extern u16 g_state_02001F6C;

void func_080C9574(u16 bitIndex, u16 enabled);
u8 func_080C9540(u16 bitIndex);
u16 func_080CE8A8(void);

void func_080CE93C(u8 reset)
{
    SelectionStats *state = &g_state_020021A0;
    u16 count;
    s32 index;

    if (reset) {
        func_080C9574(0x5A1, 0);
        func_080C9574(0x5A2, 0);
        func_080C9574(0x5A3, 0);
        func_080C9574(0x5A9, 0);
    }
    count = func_080CE8A8();
    for (index = 1; index <= 64; index++) {
        const u8 *record = g_table_08528556[index];
        u8 conditions = 0;
        u8 required = 0;
        u8 matched = 0;
        u8 threshold = record[1];
        u16 minimum;
        s32 category;

        if (threshold) {
            if (state->statistics[0][0] < threshold)
                continue;
            conditions++;
        }
        minimum = record[2] | (record[3] << 8);
        if (minimum) {
            if (g_state_02001F6C < minimum)
                continue;
            conditions++;
        }
        minimum = record[4] | (record[5] << 8);
        if (minimum) {
            if (count < minimum)
                continue;
            conditions++;
        }
        for (category = 0; category < 8; category++) {
            threshold = record[6 + category];
            if (threshold) {
                required++;
                if (state->statistics[category + 1][0] >= threshold) {
                    matched++;
                    conditions++;
                }
            }
        }
        if (required && !matched)
            continue;
        minimum = record[14] | (record[15] << 8);
        if (minimum) {
            if (!func_080C9540(minimum))
                continue;
            conditions++;
        }
        if (conditions == 0)
            state->selection = 0;
        else
            state->selection = record[0];
        break;
    }
}
