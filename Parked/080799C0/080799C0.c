#include "ffta.h"

typedef struct {
    u16 id;
    u8 quantity;
    u8 equipped;
} ItemStock;

typedef struct {
    u16 name;
    u16 description;
    u8 unknown_04[4];
    u8 category;
    u8 unknown_09[0x17];
} ItemDefinition;

typedef struct {
    u8 unknown_0000[0x1940];
    ItemStock inventory[361];
    ItemStock extra[14];
    u8 unknown_1F1C[0x2FC1 - 0x1F1C];
    u8 flags;
} SaveInventory;

typedef struct {
    u8 unknown_000[0xC1F];
    u8 slot;
    u8 unknown_C20[0x1D0C - 0xC20];
    void *unit;
} EquipmentState;

typedef struct {
    u16 position;
    u16 unavailable;
    u16 id;
    u16 unknown_06;
    u32 name;
    u16 description;
    u8 equipped;
    u8 quantity;
    u8 bank;
    u8 unknown_11;
    u16 slot;
} EquipmentRow;

typedef struct EquipmentList {
    s32 count;
    const u8 *const *strings;
    u32 unknown_08;
    u8 x, y, width, height;
    u16 tile;
    u8 style, unknown_13;
    u16 first_row;
    u8 row_height, unknown_17;
    EquipmentRow *rows;
    u8 unknown_1C[0x230 - 0x1C];
    EquipmentRow entries[0];
} EquipmentList;

extern SaveInventory g_state_02000000;
extern const u8 *const g_table_08526680[];
extern const ItemDefinition g_table_0851D180[];
extern EquipmentState *data_03002818;
extern u32 func_080CB48C(void *object, u16 entry, u8 slot);

static inline u8 collect(const ItemStock *stock, s32 length, s32 low, s32 high,
                         ItemStock *items, u16 *indices)
{
    s32 count = 0;
    s32 i;

    for (i = 0; i < length; i++) {
        s32 category = g_table_0851D180[stock[i].id].category;
        if (category >= low && category < high && stock[i].quantity) {
            indices[count] = i;
            items[count] = stock[i];
            count++;
        }
    }
    return count;
}

static inline void set_item(EquipmentRow *row, const ItemStock *item)
{
    row->id = item->id;
    row->name = g_table_0851D180[item->id].name;
    row->description = g_table_0851D180[item->id].description;
    row->equipped = item->equipped;
    row->quantity = item->quantity;
}

s32 func_080799C0(u16 mode, EquipmentList *list, u16 *selected)
{
    ItemStock items[256];
    u16 indices[256];
    EquipmentRow *rows;
    u8 inventory_count, extra_count;
    s32 total, count, i;
    EquipmentRow *row;
    u16 first = 0xFFFF;

    list->strings = g_table_08526680;
    list->x = 0;
    list->y = 0;
    list->width = 21;
    list->height = 13;
    list->tile = 0x229;
    list->style = 0;
    list->first_row = 0;
    list->row_height = 16;
    list->unknown_17 = 0;
    rows = list->entries;
    list->rows = rows;

    if (mode == 0) {
        inventory_count = collect(g_state_02000000.inventory, 361, 21, 24, items, indices);
        extra_count = collect(g_state_02000000.extra, 14, 21, 24,
                              items + inventory_count, indices + inventory_count);
    } else if (mode == 1) {
        inventory_count = collect(g_state_02000000.inventory, 361, 24, 27, items, indices);
        extra_count = collect(g_state_02000000.extra, 14, 24, 27,
                              items + inventory_count, indices + inventory_count);
    } else if (mode == 2) {
        inventory_count = collect(g_state_02000000.inventory, 361, 1, 20, items, indices);
        extra_count = collect(g_state_02000000.extra, 14, 1, 20,
                              items + inventory_count, indices + inventory_count);
    } else if (mode == 3) {
        inventory_count = collect(g_state_02000000.inventory, 361, 20, 21, items, indices);
        extra_count = collect(g_state_02000000.extra, 14, 20, 21,
                              items + inventory_count, indices + inventory_count);
    } else {
        inventory_count = collect(g_state_02000000.inventory, 361, 27, 30, items, indices);
        extra_count = collect(g_state_02000000.extra, 14, 27, 30,
                              items + inventory_count, indices + inventory_count);
    }
    row = rows;
    total = inventory_count + extra_count;
    count = 0;
    /* Both native branches compare the input ordinal with the individual bank counts. */
    if (!(g_state_02000000.flags & 2)) {
        for (i = 0; i < total; i++) {
            s32 unavailable;
            if (items[i].equipped >= items[i].quantity)
                unavailable = 1;
            else
                unavailable = func_080CB48C(data_03002818->unit, items[i].id,
                                            data_03002818->slot) & 1;
            if (!unavailable && first == 0xFFFF)
                first = count;
            row->unavailable = unavailable;
            row->position = i;
            set_item(row, &items[i]);
            if (i < inventory_count) {
                row->bank = 0;
                row->slot = indices[i];
            } else if (i < extra_count) {
                rows[count].bank = 1;
                rows[count].slot = indices[i];
            } else {
                rows[count].bank = 2;
                rows[count].slot = indices[i];
            }
            row++;
            count++;
        }
    } else {
        for (i = 0; i < total; i++) {
            s32 unavailable = 0;
            if (func_080CB48C(data_03002818->unit, items[i].id, data_03002818->slot) & 1)
                continue;
            if (items[i].equipped >= items[i].quantity)
                unavailable = 1;
            if (!unavailable && first == 0xFFFF)
                first = count;
            row->unavailable = unavailable;
            row->position = count;
            set_item(row, &items[i]);
            if (i < inventory_count) {
                row->bank = 0;
                row->slot = indices[i];
            } else if (i < extra_count) {
                rows[count].bank = 1;
                rows[count].slot = indices[i];
            } else {
                rows[count].bank = 2;
                rows[count].slot = indices[i];
            }
            row++;
            count++;
        }
    }

    if (first != 0xFFFF)
        *selected = first;
    else
        *selected = 0;
    list->count = count;
    return count;
}
