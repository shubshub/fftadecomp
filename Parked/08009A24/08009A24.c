#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 unknown_03;
} Entry08009A14;

extern u8 g_state_02000000[];
extern const u8 g_table_089C1484[];

const Entry08009A14 *func_08009A14(u16 index);

const u8 *func_08009A24(u16 index)
{
    const Entry08009A14 *entry;
    const u8 *base = g_table_089C1484;
    const u8 *result;
    u8 type;
    u8 value;

    if (index > 239)
        entry = func_08009A14(170);
    else
        entry = func_08009A14(*(const u16 *)(g_state_02000000 + 0x2192));

    type = entry->field_02;
    result = base + ((const u32 *)base)[type];
    if (index <= 239 && type == 61) {
        value = g_state_02000000[0x3C2A];
        if (value != 0)
            value--;
        result = base + ((const u32 *)result)[(u8)(value / 10u)];
    }
    return result;
}
