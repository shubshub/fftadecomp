/* Target: [0x0803652C, 0x08036584), 88 bytes.
 * f0b50006060e301cfff7c2ff021c002a1bdb00230e4950008018400040180d49
 * 451820204042071c5c1c301c211cfff7cfff011c002905d01f20014028783840
 * 08432870231c032beeddf0bc01bc004700000002362e0000
 */

#include "ffta.h"

typedef struct {
    u8 type : 5;
    u8 unknown_05 : 3;
    u8 unknown_01[5];
} __attribute__((packed)) SelectionRecord0803652C;

typedef struct {
    u8 unknown_0000[0x2E36];
    SelectionRecord0803652C records[5];
} SelectionState0803652C;

extern SelectionState0803652C g_state_02000000;
extern s32 func_080364BC(u8 type);
extern s32 func_080364FC(s32 first, s32 second);

void func_0803652C(u8 value)
{
    s32 index = func_080364BC(value);

    if (index >= 0) {
        s32 iteration = 0;
        SelectionState0803652C *state = &g_state_02000000;
        SelectionRecord0803652C *record = &state->records[index];

        for (; iteration < 4; iteration++) {
            s32 next = func_080364FC(value, iteration + 1);

            if (next != 0)
                record->type = next;
        }
    }
}
