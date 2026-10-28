#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 attributes[3];
    u8 unknown_1D[3];
} EntryRecord;

extern const EntryRecord g_table_0851D180[];
extern u8 func_0812CB64(void *unit, u8 attribute, u16 value);

/* Complete [0x0812D07C, 0x0812D0BA): 62 bytes, 27 instructions. */
u8 func_0812D07C(void *unit, u16 entry, u32 value)
{
    const EntryRecord *record = &g_table_0851D180[entry];
    s32 index;

    for (index = 0; index < 3; index++) {
        if (!func_0812CB64(unit, record->attributes[index], value))
            return 0;
    }
    return 1;
}
