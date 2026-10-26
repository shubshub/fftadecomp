#include "ffta.h"

extern const u8 g_table_08394778[];
extern const u32 g_table_08526680[];
extern u32 func_080C8570(u8 first, u8 second, u8 selector);

/* Complete [0x080CCB68, 0x080CCB94): 44 bytes, 16 instructions. */
u32 func_080CCB68(u8 index)
{
    const u32 *table = g_table_08526680;
    u8 unit = g_table_08394778[index];

    return table[func_080C8570(unit, unit, 0)];
}
