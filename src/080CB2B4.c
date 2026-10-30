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

/* Complete target: [0x080CB2B4, 0x080CB320), 108 bytes.
 * Target bytes: 10b581b00004030c002b06d120e08878c978401a0006000e1be06c460f4a10498b4205d90f48834202d80f4812180e21002c00d02160111c00220098824207da041c08889842e2d001320431a242f8db002001b010bc02bc08470000401900026901000077010000a4050000
 */
u8 func_080CB2B4(u32 identifier)
{
    u32 id = (u16)identifier;
    InventoryRecord *records;
    s32 count;
    s32 index;

    if (id == 0)
        return 0;

    records = select_inventory_bank(id, &count);
    for (index = 0; index < count; index++, records++) {
        if (records->identifier == id)
            return records->quantity - records->unknown_03;
    }
    return 0;
}
