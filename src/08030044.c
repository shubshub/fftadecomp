#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u8 unknown_04[8];
} Entry08030044;

typedef struct {
    u8 unknown_00[0xB0];
    Entry08030044 entries[0];
} Data08030044;

typedef struct {
    Data08030044 *data;
} State08030044;

u32 func_08030044(u32 index, u32 value_03, u8 value_01)
{
    State08030044 **state = (State08030044 **)0x03002810;

    (*state)->data->entries[index].field_00 = 0;
    (*state)->data->entries[index].field_01 = value_01;
    (*state)->data->entries[index].field_03 = value_03 + 1;
    (*state)->data->entries[index].field_02 = 0;
    return 0;
}
