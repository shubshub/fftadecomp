#ifndef FFTA_080CA9E8_H
#define FFTA_080CA9E8_H

#include "ffta.h"

typedef struct InventoryRecord {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord g_state_02001940[];

static inline InventoryRecord *inventory_bank(u32 identifier, s32 *count)
{
    InventoryRecord *records = g_state_02001940;
    s32 capacity = 0x169;

    if (identifier > capacity && identifier <= 0x177) {
        records += capacity;
        capacity = 14;
    }
    if (count != 0)
        *count = capacity;
    return records;
}

#endif
