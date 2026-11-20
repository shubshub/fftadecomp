#include "ffta.h"

typedef struct {
    u16 id;
    u8 quantity;
    u8 equipped;
} InventoryItem;

typedef struct {
    u16 name;
    u16 description;
    u8 unknown_04[4];
    u8 category;
    u8 unknown_09[0x17];
} ItemDefinition;

typedef struct {
    u16 index;
    u16 flags;
    u16 item_id;
    u8 unknown_06[2];
    u32 name;
    u16 description;
    u8 equipped;
    u8 quantity;
    u8 bank;
    u8 unknown_11;
    u16 slot;
} ItemRow;

typedef struct ItemList {
    int count;
    const u8 *const *strings;
    u8 unknown_08[4];
    u8 x, y, width, height;
    u16 tile;
    u8 style;
    u8 unknown_13;
    u16 scroll;
    u8 line_height;
    u8 unknown_17;
    ItemRow *rows;
    u8 unknown_1c[0x214];
    ItemRow storage[256];
} ItemList;

extern InventoryItem g_state_02001940[];
extern const ItemDefinition g_table_0851D180[];
extern const u8 *const g_table_08526680[];

static inline u8 collect_items(const InventoryItem *inventory, int length,
                               int first, int end, InventoryItem *items, u16 *slots)
{
    int count = 0;
    int i;

    for (i = 0; i < length; i++) {
        int category = g_table_0851D180[inventory[i].id].category;
        if (category >= first && category < end && inventory[i].quantity) {
            slots[count] = i;
            items[count] = inventory[i];
            count++;
        }
    }
    return count;
}

/* Complete 0x0808CBDC..0x0808D0C4, 1256 bytes. */
int func_0808CBDC(u16 category, ItemList *list)
{
    InventoryItem items[256];
    u16 slots[256];
    ItemRow *rows;
    u8 first_count, second_count;
    int count, i;

    list->strings = g_table_08526680;
    list->x = 0;
    list->y = 0;
    list->width = 22;
    list->height = 11;
    list->tile = 0x229;
    list->style = 0;
    list->scroll = 0;
    list->line_height = 16;
    list->unknown_17 = 0;
    rows = list->storage;
    list->rows = rows;

    if (category == 0) {
        first_count = collect_items(g_state_02001940, 361, 21, 24, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 21, 24,
                                     items + count, slots + count);
        count += second_count;
    } else if (category == 1) {
        first_count = collect_items(g_state_02001940, 361, 24, 27, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 24, 27,
                                     items + count, slots + count);
        count += second_count;
    } else if (category == 2) {
        first_count = collect_items(g_state_02001940, 361, 1, 20, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 1, 20,
                                     items + count, slots + count);
        count += second_count;
    } else if (category == 3) {
        first_count = collect_items(g_state_02001940, 361, 20, 21, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 20, 21,
                                     items + count, slots + count);
        count += second_count;
    } else if (category == 4) {
        first_count = collect_items(g_state_02001940, 361, 27, 30, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 27, 30,
                                     items + count, slots + count);
        count += second_count;
    } else {
        first_count = collect_items(g_state_02001940, 361, 30, 31, items, slots);
        count = first_count;
        second_count = collect_items(g_state_02001940 + 361, 14, 30, 31,
                                     items + count, slots + count);
        count += second_count;
    }

    for (i = 0; i < count; i++) {
        rows[i].index = i;
        rows[i].item_id = items[i].id;
        rows[i].flags = 0;
        rows[i].name = g_table_0851D180[items[i].id].name;
        rows[i].description = g_table_0851D180[items[i].id].description;
        if (category == 5)
            rows[i].equipped = 0xff;
        else
            rows[i].equipped = items[i].equipped;
        rows[i].quantity = items[i].quantity;
        if (i < first_count) {
            rows[i].bank = 0;
            rows[i].slot = slots[i];
        } else if (i < second_count) {
            rows[i].bank = 1;
            rows[i].slot = slots[i];
        } else {
            rows[i].bank = 2;
            rows[i].slot = slots[i];
        }
    }
    list->count = count;
    return count;
}
