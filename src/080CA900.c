#include "ffta.h"
#include "080CA900.h"

s32 func_080CA900(u16 identifier, u8 quantity)
{
    InventoryRecord *record;
    s32 count;
    s32 index;
    s32 found = 0;

    if (quantity == 0 || identifier == 0)
        return -1;

    record = select_inventory_bank(identifier, &count);
    for (index = 0; index < count; index++, record++) {
        if (record->identifier != 0 && record->identifier == identifier) {
            found = 1;
            break;
        }
    }
    if (!found) {
        record = select_inventory_bank(identifier, &count);
        for (index = 0; index < count; index++, record++) {
            if (record->identifier == 0) {
                found = 1;
                break;
            }
        }
    }
    if (!found)
        return -1;

    if (record->identifier == 0)
        record->identifier = identifier;
    record->quantity += quantity;
    if (record->quantity > 99) {
        u8 previous = record->quantity;

        record->quantity = 99;
        return (s8)(previous - 99);
    }
    return 0;
}
