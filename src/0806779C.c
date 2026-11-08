#include "ffta.h"

typedef union {
    u16 *halfwords[0];
    u8 *bytes[0];
    const u8 **text[0];
    u16 values[0][2];
} Entry0806779C;

typedef struct {
    u8 unknown_00[0x424];
    Entry0806779C entries;
} Table0806779C;

typedef struct {
    Table0806779C *table;
    u8 unknown_04[4];
    u8 mode;
} State0806779C;

extern const u16 data_08393ABC[];
extern const u16 data_08393AC4[];
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_0855A64C[];
extern const u8 *const g_table_08526680[];
extern u16 func_080CA7A4(u16 entry, u8 selector);
extern const u8 *func_080CB4E0(u32 identifier);

/* Complete target [0x0806779C, 0x080678C4), 296 bytes, 7-entry jump table.
 * 00b5021c09040b0c107a0138062800d984e080000149401800688746bc770608d8770608f4770608
 * 107806083c780608647806088c780608a4780608044a05491804c013401800888000801867e00000
 * f0675508bc3a3908044a05491804c013401800888000801859e00000f0675508c43a390811681804
 * 8013074a891809180868064b0278407803210840000210438000c01843e00000240400004ca65508
 * 116818048013064a8918091808680088002162f0a9ff00040249800b40182ee02404000080665208
 * 116818048013064a891809180968f9225200101c097840180249800040181ae02404000080665208
 * 116818048013034a89180918088863f021fe0de024040000116818048013024a8918091808680
 * 2e0240400000148006802bc0847f0675508
 */
const u8 *func_0806779C(State0806779C *state, u16 index)
{
    const u8 *const *text;
    u8 *entry;
    u32 low;
    u32 high;
    u16 code;

    switch (state->mode) {
    case 1:
        return g_table_085567F0[data_08393ABC[(s16)index]];
    case 2:
        return g_table_085567F0[data_08393AC4[(s16)index]];
    case 3:
        entry = state->table->entries.bytes[(s16)index];
        text = g_table_0855A64C;
        low = entry[0];
        high = entry[1];
        return text[(high & 3) << 8 | low];
    case 4:
        code = func_080CA7A4(*state->table->entries.halfwords[(s16)index], 0);
        return g_table_08526680[code];
    case 5:
        code = 0x1F2 + *state->table->entries.bytes[(s16)index];
        return g_table_08526680[code];
    case 6:
        return func_080CB4E0(state->table->entries.values[(s16)index][0]);
    case 7:
        return *state->table->entries.text[(s16)index];
    }
    return g_table_085567F0[0];
}
