#include "ffta.h"

/* Complete [0x080CE93C, 0x080CEA7E): 322 bytes, 141 instructions and seven
 * literal words at [0x080CEA40, 0x080CEA5C).
 * Target: f0b557464e464546e0b481b000063d49884600280fd03c480021faf70dfe3b480021faf709fe3a480021faf705fe39480021faf701fefff799ff0004000c009001229146262040448246002700218c4600254a46110130480c186178002904d04246107d88425fd30125a178e07802020a43002a06d029490888904254d3681c0006050e2179607900020843002805d0009a824248d3681c0006050e0021a61d701802784b1c002a11d0781c0006070e59004046143040180078904207d3604601300006000e8446681c0006050e191c0729e5dd002f02d06046002824d0a17be07b00020843002807d0faf78bfd0006002819d0681c0006050e002d10d151460d7016e0a0210002a1050000a2050000a3050000a9050000568552086c1f000220785246107004e001208144494640298bdd01b038bc9846a146aa46f0bc01bc0047
 *
 * The table at 0x08528556 is read in 16-byte rows and each halfword member is
 * assembled from two byte loads, so the record is packed.  Row 0 is all zero
 * and rows 1 to 64 are the ones scanned.
 *
 * The block at 0x020021A0 is held in r8 from function entry.  The ROM also
 * keeps the address of its byte 0x26 in sl for the whole scan, which pushes
 * the captured count to the stack, and reloads 0x02001F6C from the pool at
 * its one use; this source reproduces both only with the two addresses in
 * pointer variables (the direct member forms do not).  They are taken off
 * g_state_02000000, as 080CE8A8 and 080CEB34 root this state.
 */

typedef struct __attribute__((packed)) {
    u8 text_index;
    u8 first_threshold;
    u16 level;
    u16 count;
    u8 thresholds[8];
    u16 flag;
} SelectionRecord;

typedef struct {
    u8 unknown_00[0x14];
    u8 slots[9][2];
    u8 text_index;
} SelectionStats;

typedef struct {
    u8 unknown_0000[0x1F6C];
    u16 level;
    u8 unknown_1F6E[0x21A0 - 0x1F6E];
    SelectionStats stats;
} SelectionState;

extern u8 g_state_02000000[];
extern const SelectionRecord g_table_08528556[];

void func_080C9574(u16 bitIndex, u16 enabled);
u8 func_080C9540(u16 bitIndex);
u16 func_080CE8A8(void);

void func_080CE93C(u8 reset)
{
    SelectionStats *state = &((SelectionState *)g_state_02000000)->stats;
    u16 *level = &((SelectionState *)g_state_02000000)->level;
    u16 count;
    s32 index;
    s32 i;

    if (reset) {
        func_080C9574(0x5A1, 0);
        func_080C9574(0x5A2, 0);
        func_080C9574(0x5A3, 0);
        func_080C9574(0x5A9, 0);
    }
    count = func_080CE8A8();
    for (index = 1; index <= 64; index++) {
        u8 required = 0;
        u8 matched = 0;
        u8 conditions = 0;
        const SelectionRecord *record = &g_table_08528556[index];
        u8 *text_index = &state->text_index;

        if (record->first_threshold) {
            if (state->slots[0][0] < record->first_threshold)
                continue;
            conditions++;
        }
        if (record->level) {
            if (*level < record->level)
                continue;
            conditions++;
        }
        if (record->count) {
            if (count < record->count)
                continue;
            conditions++;
        }
        for (i = 0; i < 8; i++) {
            if (record->thresholds[i]) {
                required++;
                if (state->slots[i + 1][0] >= record->thresholds[i]) {
                    matched++;
                    conditions++;
                }
            }
        }
        if (required && !matched)
            continue;
        if (record->flag) {
            if (!func_080C9540(record->flag))
                continue;
            conditions++;
        }
        if (conditions == 0)
            *text_index = 0;
        else
            *text_index = record->text_index;
        break;
    }
}
