#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 index;
    u8 unknown_0A[10];
} IndexedRecord;

typedef struct {
    s32 count;
    u32 *values;
    u8 unknown_08[0x10];
    IndexedRecord *records;
} IndexedList;

/* Complete target: [0x08085450, 0x08085484), 52 bytes, 26 instructions. */
void func_08085450(void *unused, u32 *output, IndexedList *list)
{
    u16 i;

    for (i = 0; i < list->count; i++)
        *output++ = list->values[list->records[i].index];
}
