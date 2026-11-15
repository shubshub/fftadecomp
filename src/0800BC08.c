#include "ffta.h"

/* 0x0800BC08 .. 0x0800BC28: 32 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 x;
    s16 y;
    u8 unknown_1C[0x0C];
} Record0800BC08;

extern Record0800BC08 g_records_02009000[];

void func_0800BC08(u8 index, s16 x, s16 y)
{
    g_records_02009000[index].x = x;
    g_records_02009000[index].y = y;
}
