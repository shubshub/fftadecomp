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

/* Complete target: [0x080CAB24, 0x080CABA6), 130 bytes.
 * Target bytes: 70b581b00004040c09060e0e002c34d06d46134b134a944205d91348844202d812481b180e22002d00d02a601a1c002300998b420ada1088a04207d00d1c01330432ab4202da1088a042f8d18b4214d0002e0dd0d078917888420ed201300be0401900026901000077010000a4050000d078002801d00138d07001b070bc01bc0047
 */
void func_080CAB24(u16 identifier, u8 increment)
{
    InventoryRecord *records;
    s32 count;
    s32 index;

    if (identifier == 0)
        return;

    records = select_inventory_bank(identifier, &count);
    for (index = 0; index < count; index++, records++) {
        if (records->identifier == identifier)
            break;
    }
    if (index == count)
        return;

    if (increment) {
        if (records->unknown_03 < records->quantity)
            records->unknown_03++;
    } else if (records->unknown_03 != 0) {
        records->unknown_03--;
    }
}
