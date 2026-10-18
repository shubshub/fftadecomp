#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u32 field_04;
    u16 field_08;
    u16 field_0A;
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 field_0F;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 unknown_14[8];
} Entry0804C6E4;

void func_0804C6E4(Entry0804C6E4 *entries, u16 index, u32 value_04,
                   u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                   u8 value_0E, u8 value_08)
{
    entries[index].field_0A = 0;
    entries[index].field_0F = 0;
    entries[index].field_08 = value_08;
    entries[index].field_0E = value_0E;
    entries[index].field_04 = value_04;
    entries[index].field_0D = 1;
    entries[index].field_10 = value_10;
    entries[index].field_11 = value_11;
    entries[index].field_12 = value_12;
    entries[index].field_0C = 5;
    entries[index].field_13 = value_13;
}
