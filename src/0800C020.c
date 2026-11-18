#include "ffta.h"

typedef struct {
    u8 *buffer;
    u32 source;
    u16 format;
    u16 size;
    u8 width;
    u8 height;
    u16 byte_count;
    u16 field_10;
    u16 unknown_12;
    u32 field_14;
    s16 x;
    s16 y;
    u8 field_1C;
    u8 unknown_1D;
    u16 field_1E;
    u16 field_20;
    u8 unknown_22[6];
} Record02009000;

extern Record02009000 g_records_02009000[];

/* 0x0800C020..0x0800C038, 24 bytes. func_0800AFAC installs this layer size. */
u16 func_0800C020(u8 index)
{
    return g_records_02009000[index].size;
}
