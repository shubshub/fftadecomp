#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01[27];
    u8 category;
    u8 unknown_1d[35];
} Entry080114FC;

typedef struct {
    u16 count;
    u16 unknown_02;
    u32 field_04;
    u32 field_08;
    u32 field_0c;
    u32 field_10;
    Entry080114FC *entries;
} State080114FC;

extern State080114FC data_02009170;

/* Complete body 0x080114FC..0x08011564: 104 bytes including middle literal. */
void func_080114FC(u8 category)
{
    s32 index;
    for (index = 0; index < data_02009170.count; index++) {
        u32 offset = index * sizeof(Entry080114FC);
        Entry080114FC *entry = (Entry080114FC *)((u8 *)data_02009170.entries + offset);
        if (entry->active && entry->category == category)
            entry->active = 0;
    }
    switch (category) {
    case 0: data_02009170.field_08 = 0; break;
    case 1: data_02009170.field_0c = 0; break;
    case 2: data_02009170.field_04 = 0; break;
    case 3: data_02009170.field_10 = 0; break;
    }
}
