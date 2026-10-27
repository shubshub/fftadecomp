#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01;
    u16 status;
} EntryRecord;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern EntryRecord g_state_02002B08[];

/* 080612C8..0806130C: 68 bytes. */
u8 func_080612C8(EntryRecord **output)
{
    EntryRecord *entry;
    u32 count;
    s32 remaining;

    g_callbacks_0836D4B8[0](output, 264);
    entry = g_state_02002B08;
    count = 0;
    for (remaining = 63; remaining >= 0; remaining--, entry++) {
        if (entry->active != 0 && entry->status == 0) {
            *output++ = entry;
            count++;
        }
    }
    return count;
}
