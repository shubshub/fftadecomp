#include "ffta.h"

/* 0x080A88EC..0x080A88F6: 10 bytes, 5 instructions. */
typedef struct {
    u8 unknown_00[0x2C4];
} IndexedRecord;

IndexedRecord *func_080A88EC(IndexedRecord *records, s32 index)
{
    return &records[index];
}
