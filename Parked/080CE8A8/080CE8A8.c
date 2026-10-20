#include "080CE8A8.h"

extern const u16 g_table_08529EE4[];

u8 func_080C9540(u16 bitIndex);

u16 func_080CE8A8(void)
{
    u32 count = 0;
    u32 index;
    u16 entry;

    for (index = 0; (entry = g_table_08529EE4[index]) != 0xFFFF; index++) {
        if (func_080C9540(entry + 0x2FF))
            count++;
    }
    if (func_080C9540(0x36) ||
        contains_category(((const CategoryState *)g_state_02000000)->head, 0x17F))
        count++;
    return count;
}
