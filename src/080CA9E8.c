#include "080CA9E8.h"

s32 func_080CA9E8(u16 identifier, u8 quantity)
{
    InventoryRecord *record;
    s32 count;
    s32 index;
    s32 found = 0;

    if (quantity == 0)
        return 0;
    if (identifier == 0)
        return -1;
    record = inventory_bank(identifier, &count);
    for (index = 0; index < count; index++, record++) {
        if (record->identifier != 0 && record->identifier == identifier) {
            found = 1;
            break;
        }
    }
    if (!found)
        return -1;
    if (record->quantity > quantity)
        record->quantity -= quantity;
    else
        record->quantity = 0;
    return 0;
}
