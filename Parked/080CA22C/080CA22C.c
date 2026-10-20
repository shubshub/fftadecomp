#include "ffta.h"

typedef struct {
    u8 unknown_00[7];
    u8 category;
    u8 unknown_08[0x20];
    u16 flags;
} CategoryFlagRecord;

u32 func_080C92F0(void *data, u32 selector);

void func_080CA22C(void *object)
{
    CategoryFlagRecord *record = object;
    u32 index = func_080C92F0(record, 0x21);

    if (index != 0) {
        u8 *values = (u8 *)record + 0x40;

        values[index] = 0xE4;
    }
    if (record->category != 0) {
        if (record->category == 0x44 || record->category == 0x45)
            record->flags |= 0x800;
    }
}
