#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 category;
    u8 unknown_05[0x2F];
} CategoryRecord;

extern const CategoryRecord g_table_08521A14[];

u32 func_080C8570(u8 first, u8 second, u8 selector);

u8 func_080C94D0(u8 category, u16 value)
{
    u16 index;

    if (value == 0)
        return 0;
    for (index = 0; index < 116; index++) {
        u32 offset = index * sizeof(CategoryRecord);
        const CategoryRecord *record = (const CategoryRecord *)
            ((const u8 *)g_table_08521A14 + offset);

        if (record->category == category) {
            u16 lower = func_080C8570(index, index, 0x25);
            u16 upper = func_080C8570(index, index, 0x26);

            if (lower <= value && upper >= value)
                return index;
        }
    }
    return 0;
}
