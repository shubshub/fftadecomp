#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 group;
    u8 unknown_07[0x35];
    u8 entry;
} EntrySelection;

typedef struct {
    u8 unknown_00[4];
    u16 table_index;
} EntryInfo;

extern const EntryInfo *func_080CD480(u8 group, u8 entry);
extern const u8 data_0852736C[][4];

/* Target: [0x0812E3B0, 0x0812E3E8), 56 bytes, 25 instructions. */
u8 func_0812E3B0(const EntrySelection *selection)
{
    const EntryInfo *info = func_080CD480(selection->group, selection->entry);
    if (info->table_index != 0) {
        const u8 *record = data_0852736C[info->table_index];
        u32 low = record[1] >> 5;
        u8 mask = 3;
        u32 high = record[2];

        return ((high & mask) << 3) | low;
    }
    return 0;
}
