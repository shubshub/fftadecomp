#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CB1F4(u16 identifier);

/* 0x08026A7C..0x08026AB8: 60 complete bytes.
 * Target: 30b581b000206946a4f0c4fb041c00250ce02088a4f0b0fb0006002804d0a078002801d0012005e00135043400988542efdb002001b030bc02bc0847.
 */
u8 func_08026A7C(void)
{
    InventoryRecord *records;
    s32 count;
    s32 i;

    records = func_080CB210(0, &count);
    for (i = 0; i < count; i++, records++) {
        if (func_080CB1F4(records->identifier) && records->quantity != 0)
            return 1;
    }
    return 0;
}
