#include "ffta.h"

/* Complete [0x0802ECEC, 0x0802ED88): 156 bytes, 70 instructions, including
 * the literal pool.
 * f0b54f464646c0b40006000e8446114a11680020487200231068c079834237da0d48614656390906
 * 090e8846151c0b4989460b4944180126604655300006070e208800281ed0404654280bd821886046
 * 55380fe044f4000200000002348f5208343c0000052f07d820880001484401786046aa38814205d1
 * 2868311c9940427a11434172023401332868c0798342d7db18bc9846a146f0bc01bc0047
 */

typedef struct {
    u8 x;
    u8 unknown_01;
    u8 y;
    u8 unknown_03[4];
    u8 count;
    u8 tile_offset;
    u8 selected;
} ListState;

typedef struct Root0802ECEC {
    u8 unknown_0000[0x3C34];
    u16 items[0];
} Root0802ECEC;

typedef struct {
    u8 value;
    u8 unknown_01[15];
} BaseEntry0802ECEC;

extern ListState *data_0200F444;
extern Root0802ECEC g_state_02000000;
extern const BaseEntry0802ECEC g_table_08528F34[];

void func_0802ECEC(u8 filter)
{
    s32 index;

    data_0200F444->selected = 0;
    for (index = 0; index < data_0200F444->count; index++) {
        if (g_state_02000000.items[index] != 0) {
            if (filter >= 0x56 && filter <= 0xAA) {
                if (g_state_02000000.items[index] == filter - 0x55)
                    data_0200F444->selected |= 1 << index;
            } else if (filter >= 0xAB && filter <= 0xB0) {
                if (g_table_08528F34[g_state_02000000.items[index]].value ==
                    filter - 0xAA)
                    data_0200F444->selected |= 1 << index;
            } else {
                data_0200F444->selected |= 1 << index;
            }
        }
    }
}
