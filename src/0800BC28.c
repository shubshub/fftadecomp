#include "ffta.h"

/* 0x0800BC28..0x0800BC4C: 36 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 x;
    s16 y;
    u8 unknown_1C[0x0C];
} Record0800BC28;

extern Record0800BC28 g_records_02009000[];

void func_0800BC28(u8 index, s16 *x, s16 *y)
{
    *x = g_records_02009000[index].x;
    *y = g_records_02009000[index].y;
}
