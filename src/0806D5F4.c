#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord0806D5F4;

extern InventoryRecord0806D5F4 *func_080CB210(u32 identifier, s32 *count);

/* Target [0x0806D5F4, 0x0806D664), 112 complete bytes:
 * 10b581b0012069465df008fe031c0022009882420dda041c9000c11808880028
 * 02d08878002817d1501c0004020ca242f2dbb520400069465df0f0fd031c0022
 * 009882420fda041c9000c1180888002804d08878002801d0012005e0501c0004
 * 020ca242f0db002001b010bc02bc0847
 */
u8 func_0806D5F4(void)
{
    InventoryRecord0806D5F4 *records;
    s32 count;
    u16 i;

    records = func_080CB210(1, &count);
    for (i = 0; i < count; i++) {
        if (records[i].identifier != 0 && records[i].quantity != 0)
            return 1;
    }
    records = func_080CB210(0x16A, &count);
    for (i = 0; i < count; i++) {
        if (records[i].identifier != 0 && records[i].quantity != 0)
            return 1;
    }
    return 0;
}
