#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2A];
    u16 entries[5];
} EntryObject;

s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA4F0(const void *object, u8 selector)
{
    s32 sum = 0;
    s32 index;

    for (index = 0; index < 5; index++) {
        if (((const EntryObject *)object)->entries[index] != 0)
            sum += func_080CA7A4(((const EntryObject *)object)->entries[index], selector);
    }
    return sum;
}
