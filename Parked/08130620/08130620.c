#include "ffta.h"

struct LookupRecord {
    u8 unknown0[0x1A];
    u8 values[3];
    u8 unknown1D[3];
};

extern const struct LookupRecord g_table_0851D180[];

u8 func_08130620(u16 entry)
{
    if (entry != 0) {
        const struct LookupRecord *record = &g_table_0851D180[entry];
        s32 index;

        for (index = 0; index < 3; index++) {
            if (record->values[index] == 0x3F)
                return 1;
        }
    }
    return 0;
}
