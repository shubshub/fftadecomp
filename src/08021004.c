#include "ffta.h"

extern const u8 *const g_table_08390E44[];

const u8 *func_08021004(u32 index, u32 selector)
{
    const u8 *entries = g_table_08390E44[index];
    s32 variant = selector & 3;
    u32 offset;

    switch (variant) {
    case 1:
    case 2:
        offset = (selector & ~3) * 6 + 12;
        break;
    default:
        offset = (selector & ~3) * 6;
        break;
    }
    return entries + offset;
}
