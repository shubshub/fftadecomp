#include "ffta.h"

extern const u8 g_table_08394778[];

u32 func_080C8570(u8 first, u8 second, u8 selector);

u8 func_080CCAE8(u8 index)
{
    u8 value = g_table_08394778[index];

    return func_080C8570(value, value, 1);
}
