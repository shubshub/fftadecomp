#ifndef INVENTORY_UPDATE_080CA900_H
#define INVENTORY_UPDATE_080CA900_H

typedef struct InventoryRecord {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord g_state_02001940[];

static inline InventoryRecord *select_inventory_bank(u32 identifier, s32 *count)
{
    InventoryRecord *records = g_state_02001940;
    s32 length = 0x169;

    if (identifier > length && identifier <= 0x177) {
        records += 0x169;
        length = 14;
    }
    if (count != 0)
        *count = length;
    return records;
}

#endif
