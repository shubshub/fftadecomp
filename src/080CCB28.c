#include "ffta.h"

/* 0x080CCB28..0x080CCB48: 32 bytes, 13 instructions, including a pool. */
extern const u8 g_table_08394778[];
extern u8 func_080C8570(u8 first, u8 second, u8 mode);

u32 func_080CCB28(u8 index)
{
    u8 value = g_table_08394778[index];

    return func_080C8570(value, value, 6);
}
