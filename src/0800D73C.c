#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 start;
    u8 end;
    u8 unknown_04[24];
} RangeEntry;

extern RangeEntry *func_0800C614(u32 handle);

static inline RangeEntry *get_range_entry(u32 handle, u8 kind, u8 index)
{
    RangeEntry *entry = 0;

    switch (kind) {
    case 0:
        entry = func_0800C614(handle);
        break;
    case 1:
        entry = &func_0800C614(handle)[index];
        break;
    case 2:
        entry = &func_0800C614(handle)[index];
        break;
    }
    return entry;
}

void func_0800D73C(u32 handle, u8 kind, u8 index, s16 start, s16 end)
{
    RangeEntry *entry = get_range_entry(handle, kind, index);

    if (start < 0)
        start = 0;
    else if (start >= 160)
        start = 160;
    if (end < 0)
        end = 0;
    else if (end >= 160)
        end = 159;
    entry->start = start;
    entry->end = end;
}
