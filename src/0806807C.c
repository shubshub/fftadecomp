#include "ffta.h"

typedef struct {
    u16 id;
    u8 quantity;
    u8 reference_quantity;
} Item;

extern Item g_state_02001940[];
extern Item data_02001EE4[];

/* Complete target: [0x0806807C, 0x080680E0), 100 bytes, 46 instructions. */
u32 func_0806807C(void)
{
    Item *item = g_state_02001940;
    s32 i;

    for (i = 0; i <= 360; i++, item++) {
        if (item->id != 0 && item->id != 0x33 && item->id != 0x94 &&
            item->id != 0x11E && item->id != 0x12E &&
            item->quantity > item->reference_quantity)
            return 1;
    }
    item = data_02001EE4;
    for (i = 0; i <= 13; i++, item++) {
        if (item->id != 0 && item->quantity != 0)
            return 1;
    }
    return 0;
}
