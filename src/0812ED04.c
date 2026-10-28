#include "ffta.h"

/* 0x0812ED04..0x0812ED58: 84 bytes. */
typedef struct {
    u8 unknown_00[0x1A];
    u8 values[3];
    u8 unknown_1d[3];
} LookupRecord;

extern const LookupRecord g_table_0851D180[];
extern u32 func_080C7EA4(void *unit, u8 field);

u8 func_0812ED04(void *unit, u16 value)
{
    s32 slot;
    for (slot = 0; slot < 5; slot++) {
        u16 entry = func_080C7EA4(unit, slot + 29);
        if (entry != 0) {
            const LookupRecord *record = &g_table_0851D180[entry];
            u16 index;
            for (index = 0; index < 3; index++) {
                if (record->values[index] == value)
                    return 1;
            }
        }
    }
    return 0;
}
