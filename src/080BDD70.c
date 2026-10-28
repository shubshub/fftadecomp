#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u32 value;
    u8 unknown_0C;
    u8 first;
    u8 second;
} ValueRecord;

/* 0x080BDD70..0x080BDD7C: 12 bytes. */
u32 func_080BDD70(const ValueRecord *record, u8 *first, u8 *second)
{
    *first = record->first;
    *second = record->second;
    return record->value;
}
