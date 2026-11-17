#include "ffta.h"
// Target: 0x08043DF4..0x08043ECC, 216 bytes including literals.
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u8 func_080C9540(u16 bit_index);
extern const u16 data_081499AC[5];
extern const u32 g_table_085567F0[];
extern const u16 data_0852A13E[];
extern const u8 g_table_08526680[];
typedef struct {
    u16 index;
    u16 enabled;
    u16 count;
    u16 unknown_06;
    u32 value;
    u16 size;
    u8 unknown_0e[6];
} Item;
typedef struct {
    u32 count;
    const u8 *table;
    u32 unknown_08;
    u8 field_0c, field_0d, field_0e, field_0f;
    u16 field_10;
    u8 field_12, unknown_13;
    u16 field_14;
    u8 field_16, field_17;
    Item *items;
    u8 unknown_1c[0x214];
    Item storage[5];
} State;
int func_08043DF4(State *state, int kind)
{
    u16 ids[5];
    int i;
    int count;
    int height;
    Item *items;
    func_081443FC(ids, data_081499AC, sizeof(ids));
    items = state->storage;
    state->items = items;
    count = 0;
    for (i = 0; i < 5; i++) {
        if (i == 1 && !func_080C9540(0x303))
            continue;
        if (i == 2 && !func_080C9540(0x559))
            continue;
        items[count].index = count;
        items[count].enabled = 1;
        items[count].count = i;
        items[count].value = g_table_085567F0[ids[i]];
        items[count].size = data_0852A13E[ids[i]];
        count++;
    }
    if (count > 6)
        height = 15;
    else
        height = count * 2 + 3;
    state->table = g_table_08526680;
    state->field_0c = 0;
    state->field_0d = 0;
    state->field_0e = kind;
    state->field_0f = height;
    state->field_10 = 0xcb;
    state->field_12 = 0;
    state->field_14 = 0;
    state->field_16 = 16;
    state->field_17 = 0;
    state->count = count;
    return count;
}
