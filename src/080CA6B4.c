#include "ffta.h"

typedef struct {
    u8 unknown_00[0x22];
    s16 value;
    u8 unknown_24[6];
    u16 entries[5];
} StatObject;

s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA6B4(const void *data, u8 enabled)
{
    const StatObject *object = data;
    s16 value = object->value;

    if (enabled) {
        s32 sum = 0;
        s32 index;

        for (index = 0; index < 5; index++) {
            if (object->entries[index] != 0)
                sum += func_080CA7A4(object->entries[index], 0xB);
        }
        value += sum;
    }
    if (value > 999)
        return 999;
    return value;
}
