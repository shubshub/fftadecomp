#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2A];
    u16 entries[5];
    u8 unknown_34[0x9E];
    s16 value;
} StatObject;

s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA580(const void *object)
{
    const StatObject *record = object;
    s16 value = record->value;
    s32 sum = 0;
    s32 index;

    for (index = 0; index < 5; index++) {
        if (record->entries[index] != 0)
            sum += func_080CA7A4(record->entries[index], 0x0E);
    }
    value += sum;
    if (value < 0)
        value = 0;
    return value;
}
