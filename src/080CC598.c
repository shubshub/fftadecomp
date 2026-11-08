/* Target [0x080CC598, 0x080CC65C), 196 bytes:
 * 70 b5 84 46 0d 1c 16 1c 00 22 01 23 03 48 04 49 40 18 04 4c 01 78 20 78
 * 0e e0 00 00 00 00 00 02 68 1f 00 00 92 47 39 08 50 1c 00 06 02 0e 58 1c
 * 00 06 03 0e 10 19 00 78 81 42 01 d9 00 28 f3 d1 10 4c 64 44 81 20 40 00
 * 60 44 00 78 40 00 21 78 40 18 01 1c 59 43 48 01 40 1a 80 00 40 18 c0 00
 * 28 60 09 49 88 42 00 d9 29 60 00 22 61 46 08 79 02 28 01 d0 0f 28 09 d1
 * 21 78 c8 00 40 1a 00 06 03 0e 19 e0 03 01 00 00 9f 86 01 00 01 23 0c 4c
 * 61 46 48 7a 21 78 88 42 0e d9 00 29 0c d0 01 1c 50 1c 00 06 02 0e 58 1c
 * 00 06 03 0e 10 19 00 78 81 42 01 d9 00 28 f3 d1 33 70 70 bc 01 bc 00 47
 * 8c 47 39 08
 */
#include "ffta.h"

struct StateByteAt1F68 {
    u8 unknown_0000[0x1F68];
    u8 value_1F68;
};

struct Unit080CC598 {
    u8 unknown_0000[4];
    u8 kind;
    u8 unknown_0005[4];
    u8 level;
    u8 unknown_000A[0xF8];
    u8 count;
    u8 base;
};

extern struct StateByteAt1F68 g_state_02000000;

/* ROM byte thresholds, each list terminated by 0 */
extern const u8 data_08394792[];
extern const u8 data_0839478C[];

void func_080CC598(struct Unit080CC598 *unit, u32 *out_value, u8 *out_rank)
{
    u8 i;
    u8 j;
    u8 rank;
    u32 value;

    i = 0;
    rank = 1;
    while (g_state_02000000.value_1F68 > data_08394792[i]
           && data_08394792[i] != 0) {
        i++;
        rank++;
    }

    value = (unit->base + unit->count * 2) * rank * 1000;
    *out_value = value;
    if (value > 99999)
        *out_value = 99999;

    j = 0;
    if (unit->kind == 2 || unit->kind == 15) {
        rank = unit->base * 7;
    } else {
        rank = 1;
        while (unit->level > data_0839478C[j] && data_0839478C[j] != 0) {
            j++;
            rank++;
        }
    }
    *out_rank = rank;
}
