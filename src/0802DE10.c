#include "ffta.h"

typedef struct SearchRecord {
    u8 unknown_00[0x104];
    u8 identifier;
    u8 unknown_105[3];
} SearchRecord;

typedef struct __attribute__((packed)) SearchSelector {
    u16 identifier : 4;
    u16 count : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} SearchSelector;

extern SearchRecord g_state_02000080[24];
extern u8 func_080C832C(SearchRecord *record);

/* 0802DE10..0802DE58: 72 bytes, 33 instructions. */
SearchRecord *func_0802DE10(const SearchSelector *selector)
{
    SearchRecord *record = g_state_02000080;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        if (record->identifier != 0xFF &&
            record->identifier == selector->identifier &&
            func_080C832C(record))
            return record;
    }
    return 0;
}
