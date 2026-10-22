#include "ffta.h"

extern const u8 g_table_085573F4[];

u8 func_080C9540(u16 index);
u8 func_080C95A8(u16 index);

u32 func_080D1B80(const u8 **output, u32 capacity, u32 filter)
{
    u32 count = 0;
    u32 remaining;
    const u8 *row;
    s32 index;

    (*(void (**)(void *, s32))0x0836D4B8)(output, capacity << 2);
    row = g_table_085573F4;
    remaining = capacity;
    for (index = 1; index < 128; index++, row += 8) {
        u16 condition;

        if (row[0] == 0)
            continue;
        if (row[1] != 0 && row[1] != filter)
            continue;
        condition = row[2] | (row[3] << 8);
        if (condition > 0x5FF) {
            condition -= 0x600;
            if (func_080C95A8(condition) < row[4])
                continue;
        } else {
            if (func_080C9540(condition) == 1 && row[4] == 0)
                continue;
            if (func_080C9540(condition) == 0 && row[4] == 1)
                continue;
        }
        condition = row[5] | (row[6] << 8);
        if (condition > 0x5FF) {
            condition -= 0x600;
            if (func_080C95A8(condition) >= row[7])
                continue;
        } else if (condition != 0) {
            u8 value = func_080C9540(condition);

            if (value == 1 && row[7] == 1)
                continue;
            if (value == 0 && row[7] == 0)
                continue;
        }
        *output++ = row;
        count++;
        if (--remaining == 0)
            break;
    }
    return count;
}
