#include "ffta.h"

struct UnitInfo {
    u8 unknown[5];
    u8 index;
};

struct DefaultRecord {
    u8 unknown0[0x32];
    u8 value;
    u8 unknown33;
};

struct IndexedRecord {
    u8 unknown0[0x1A];
    u8 value;
    u8 unknown1B;
};

extern const struct DefaultRecord g_table_08521A14[];
extern const struct IndexedRecord data_0855187C[];

u8 func_0813413C(const struct UnitInfo *unit, u16 entry)
{
    if (entry != 0) {
        const struct IndexedRecord *record = &data_0855187C[entry];
        return record->value;
    } else {
        const struct DefaultRecord *record = &g_table_08521A14[unit->index];
        return record->value;
    }
}
