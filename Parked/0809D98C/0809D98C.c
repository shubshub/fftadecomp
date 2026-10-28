#include "ffta.h"

/* 0x0809D98C..0x0809D9D8: 76 bytes. */
typedef struct {
    u32 key;
    Rec5 *record;
    u8 unknown_08[0xAC];
} RecordEntry;

typedef struct {
    u8 unknown_00[8];
    RecordEntry entries[13];
} RecordTable;

static inline RecordEntry *find_entry(RecordTable *table, u32 key)
{
    s32 index = 0;
    RecordEntry *entry = table->entries;

    do {
        if (entry->key == key)
            return entry;
        ++entry;
    } while (++index < 13);
    return 0;
}

void func_0809D98C(RecordTable *table, u32 key, u16 first, u16 second,
                   u16 third, u16 fourth)
{
    RecordEntry *entry = find_entry(table, key);

    if (entry != 0) {
        s32 initial = (s16)first;
        Rec5 *record = entry->record;

        record->f2 = initial;
        record->f3 = second;
        record->f4 = third;
        record->f5 = fourth;
        record->f1 = initial;
    }
}
