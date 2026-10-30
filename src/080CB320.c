#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord g_state_02001940[];

static inline InventoryRecord *select_inventory_bank(u32 id, s32 *count)
{
    InventoryRecord *records = g_state_02001940;
    s32 length = 0x169;

    if (id > length && id <= 0x177) {
        records += 0x169;
        length = 14;
    }
    if (count != 0)
        *count = length;
    return records;
}

/* Complete target: [0x080CB320, 0x080CB388), 104 bytes.
 * Target bytes: 10b581b00004030c002b02d11fe001201ee06c46104a11498b4205d91048834202d8104812180e21002c00d02160111c0022009882420ada041c0888984202d188780028e3d101320431a242f5db002001b010bc02bc0847401900026901000077010000a4050000
 */
u8 func_080CB320(u32 identifier)
{
    u32 id = (u16)identifier;
    InventoryRecord *records;
    s32 count;
    s32 index;

    if (id == 0)
        return 0;

    records = select_inventory_bank(id, &count);
    for (index = 0; index < count; index++, records++) {
        if (records->identifier == id && records->quantity != 0)
            return 1;
    }
    return 0;
}
