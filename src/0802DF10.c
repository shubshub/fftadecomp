#include "ffta.h"

typedef struct {
    u16 category : 4;
    u16 value : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} __attribute__((packed)) CategoryEntry;

extern CategoryEntry data_02003C3C[24];

/* 0802DF10..0802DF50: 64 bytes. */
u8 func_0802DF10(u8 category)
{
    s32 count = 0;
    CategoryEntry *entry = data_02003C3C;
    s32 index;

    for (index = 0; index < 24; index++, entry++) {
        if (entry->value == 0)
            return count;
        if (entry->category == category)
            count++;
    }
    return count;
}
