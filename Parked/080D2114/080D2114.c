#include "ffta.h"

typedef struct {
    u16 value00;
    u16 value02;
    u16 value04;
    u8 unknown06[2];
    u8 value08;
    u8 value09;
    u8 value0A;
    u8 value0B;
    u8 value0C;
    u8 value0D;
    u16 value0E;
    s8 value10;
    s8 value11;
    s8 value12;
    s8 value13;
    s8 value14;
    s8 value15;
    s8 value16;
    s8 value17;
    u8 unknown18[5];
    u8 value1D;
    u8 unknown1E[2];
} EntryRecord;

typedef struct {
    u8 unknown_0000[0x1F6C];
    u16 level;
} SelectionStateView;

extern const EntryRecord g_table_0851D180[];
extern u8 g_state_02000000[];

u32 func_08002804(void);

u16 func_080D2114(void)
{
    const SelectionStateView *state = (const SelectionStateView *)g_state_02000000;
    u16 level = state->level;
    u32 mask;
    s32 count;
    s32 entry;
    s32 selected;

    if (level <= 10)
        mask = 0x90;
    else if (level <= 20)
        mask = 0xA0;
    else
        mask = 0xC0;

    for (count = 0, entry = 1; entry <= 0x177; entry++) {
        if (g_table_0851D180[entry].value0C & mask)
            count++;
    }
    if (count == 0)
        return 0;

    selected = (s16)func_08002804() % count;
    for (entry = 1; entry <= 0x177; entry++) {
        if (g_table_0851D180[entry].value0C & mask) {
            if (selected == 0)
                return entry;
            selected--;
        }
    }
    return 0;
}
