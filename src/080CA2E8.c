#include "ffta.h"

typedef struct {
    u8 unknown_00[0x3D];
    u8 category;
    u8 unknown_3E[0xBE];
    u8 cached[4];
} CachedRecord;

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

u32 func_080C92F0(void *data, u32 selector);
u8 func_080CD95C(const Object *object);
s32 func_080CA4F0(const void *object, u8 selector);

void func_080CA2E8(void *object)
{
    CachedRecord *record = object;
    u8 first = func_080C92F0(record, 0x22);
    u8 second = func_080C92F0(record, 0x23);
    u8 third = func_080C92F0(record, 0x1F);
    u8 *cached;

    if (func_080CD95C((const Object *)record) && first != 1)
        first = 1;
    switch (record->category) {
    case 2:
        third++;
        break;
    case 3:
        third += 2;
        break;
    case 4:
        second = 5;
        break;
    case 5:
        if (second == 1 || second == 2)
            second = 3;
        break;
    case 6:
        first = 3;
        break;
    }
    third += func_080CA4F0(record, 0x11);
    cached = record->cached;
    cached[0] = first;
    cached[1] = second;
    cached[2] = third;
    cached[3] = ~third;
}
