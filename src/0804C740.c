#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 field_08;
    u8 unknown_0A[2];
    u8 field_0C;
    u8 field_0D;
    u8 unknown_0E[2];
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 unknown_16[6];
} Entry0804C740;

void func_0804C740(Entry0804C740 *entries, u16 index, u16 value_08,
                   u8 value_10, u8 value_11, u8 value_14,
                   u8 value_12, u8 value_13)
{
    entries[index].field_08 = value_08;
    entries[index].field_0D = 1;
    entries[index].field_10 = value_10;
    entries[index].field_11 = value_11;
    entries[index].field_12 = value_12;
    entries[index].field_0C = 2;
    entries[index].field_13 = value_13;
    entries[index].field_14 = value_14;
}
