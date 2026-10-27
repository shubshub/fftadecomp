#include "ffta.h"

/* 0x0800BCE0 .. 0x0800BD24: 68 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x16];
} Record0800BCE0;

extern Record0800BCE0 g_records_02009000[];

void func_0800BCE0(u8 index, u8 enabled)
{
    if (enabled)
        g_records_02009000[index].flags |= 8;
    else
        g_records_02009000[index].flags &= 0xFFF7;
}
