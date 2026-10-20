#include "080D2300.h"

typedef struct {
    u8 unknown_00[0x0D];
    u8 value;
    u8 unknown_0E[2];
} TableEntry;

extern const TableEntry g_table_08521214[];

s32 func_080D2300(u16 identifier)
{
    s32 total = 0;
    const SelectionRecord *record = find_record(((const State *)g_state_02000000)->head, identifier);

    if (record == 0)
        return 0;
    if (record->first_index != 0)
        total += g_table_08521214[record->first_index].value;
    if (record->second_index != 0)
        total += g_table_08521214[record->second_index].value;
    if (total < 0)
        total = 0;
    return total;
}
