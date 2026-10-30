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

extern const struct DefaultRecord g_table_08521A14[];

/* 08130820..08130834: 20 bytes, including literal pool.
 * 41793420484302494018333000787047141a5208
 */
u8 func_08130820(const struct UnitInfo *unit)
{
    u8 index = unit->index;
    const struct DefaultRecord *record = &g_table_08521A14[index];

    return record->unknown33;
}
