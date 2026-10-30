#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CB1F4(u16 identifier);
extern u32 func_080CB450(Unit *unit, u16 identifier);

/* 0x08026A30..0x08026A7C: 76 complete bytes.
 * Target: 70b581b0061c00206946a4f0e9fb041c002513e02088a4f0d5fb000600280bd0a078002808d02188301ca4f0f9fc0006002801d0012005e00135043400988542e8db002001b070bc02bc0847.
 */
u32 func_08026A30(Unit *unit)
{
    InventoryRecord *records;
    s32 count;
    s32 i;

    records = func_080CB210(0, &count);
    for (i = 0; i < count; i++, records++) {
        if (func_080CB1F4(records->identifier) && records->quantity != 0 &&
            (u8)func_080CB450(unit, records->identifier))
            return 1;
    }
    return 0;
}
