#include "ffta.h"
extern void *memcpy(void *, const void *, unsigned long);
extern const u16 data_081499B6[4];
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
    Item storage[4];
} State;
/* Target: 0x08043ECC..0x08043F64, 152 bytes including literals. */
int func_08043ECC(State *state, int kind)
{
    u16 ids[4];
    int i;
    int count;
    Item *item;
    Item *items;
    memcpy(ids, data_081499B6, sizeof(ids));
    items = state->storage;
    state->items = items;
    for (i = 0; i < 4; i++) {
        item = &items[i];
        item->index = i;
        item->enabled = 1;
        item->count = i;
        item->value = g_table_085567F0[ids[i]];
        item->size = data_0852A13E[ids[i]];
    }
    count = sizeof(ids) / sizeof(ids[0]);
    state->table = g_table_08526680;
    state->field_0c = 0;
    state->field_0d = 0;
    state->field_0e = kind;
    state->field_0f = 11;
    state->field_10 = 0x24b;
    state->field_12 = 0;
    state->field_14 = 0;
    state->field_16 = 16;
    state->field_17 = 0;
    state->count = count;
    return count;
}
