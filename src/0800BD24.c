#include "ffta.h"

/* 0x0800BD24 .. 0x0800BD68: 68 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x16];
} Record0800BD24;

extern Record0800BD24 g_records_02009000[];

void func_0800BD24(u8 index, u8 enabled)
{
    if (enabled)
        g_records_02009000[index].flags |= 0x20;
    else
        g_records_02009000[index].flags &= 0xFFDF;
}
