#include "ffta.h"

struct Record0812F358 {
    u8 unknown_00;
    u8 kind;
    u8 unknown_02;
    u8 variant;
};

struct State0812F358 {
    u8 unknown_00[0x30];
    struct Record0812F358 *record;
};

extern struct State0812F358 data_0200F3F0;
extern u8 func_08133970(u8 kind);

/* Target: [0x0812F358, 0x0812F39A), 66 bytes, 30 instructions. */
u8 func_0812F358(void)
{
    struct State0812F358 *state = &data_0200F3F0;

    if (state->record->kind == 0x3b) {
        switch (state->record->variant) {
        case 9:
            return 6;
        case 17:
            return 7;
        case 6:
            return 4;
        }
    }
    return func_08133970(state->record->kind);
}
