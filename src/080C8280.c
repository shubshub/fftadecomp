#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value;
} HalfwordRecord;

u8 func_080C8280(const void *object)
{
    const HalfwordRecord *record = object;
    u8 result = 0;

    if (record != 0 && record->value == 0)
        result = 1;
    return result;
}
