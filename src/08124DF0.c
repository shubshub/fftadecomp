#include "ffta.h"

/* 0x08124DF0..0x08124E74: 132 bytes, including the literal pool. */
typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 flags;
} Coordinate;

typedef struct {
    Coordinate entries[32];
    u32 count;
} CoordinateList;

extern const u32 data_08A19D18[];
extern CoordinateList *func_08121C58(u8);
extern u8 func_0801CC18(u8, u8);

static inline int read_u16(const u8 *bytes)
{
    u8 low = bytes[0];
    u8 high = bytes[1];

    return (high << 8) | low;
}

u8 func_08124DF0(u16 index, u8 selection)
{
    const u8 *record = (const u8 *)data_08A19D18 + data_08A19D18[index];
    const u8 *source = record + 2;
    CoordinateList *list = func_08121C58(selection);
    Coordinate *entry;
    int i;

    {
        u32 *count = &list->count;
        *count = read_u16(record);
    }
    entry = list->entries;
    for (i = 0; i < read_u16(record);) {
        entry->x = source[0];
        entry->y = source[1];
        entry->height = func_0801CC18(entry->x, entry->y);
        entry->flags = 0;
        ++i;
        source += 2;
        ++entry;
    }
    return list->count;
}
