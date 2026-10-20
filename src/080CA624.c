#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
    s16 value;
    u8 unknown_22[8];
    u16 entries[5];
} StatObject;

s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA624(const void *object, u8 enabled)
{
    const StatObject *record = object;
    s16 value = record->value;

    if (enabled) {
        s32 sum = 0;
        s32 index;

        for (index = 0; index < 5; index++) {
            if (record->entries[index] != 0)
                sum += func_080CA7A4(record->entries[index], 0x0A);
        }
        value += sum;
    }
    if (value > 999)
        return 999;
    return value;
}
