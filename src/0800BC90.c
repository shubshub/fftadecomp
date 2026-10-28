#include "ffta.h"

/* 0x0800BC90 .. 0x0800BCE0: 80 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x0A];
    u8 value;
    u8 unknown_1D[0x0B];
} Record0800BC90;

extern Record0800BC90 g_records_02009000[];

void func_0800BC90(u8 index, u8 enabled, u8 value)
{
    if (enabled) {
        g_records_02009000[index].flags |= 4;
        g_records_02009000[index].value = value;
    } else {
        g_records_02009000[index].flags &= 0xFFFB;
        g_records_02009000[index].value = 0xFF;
    }
}
