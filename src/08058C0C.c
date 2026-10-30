#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord08058C0C;

extern InventoryRecord08058C0C *func_080CB210(u32 identifier, s32 *count);

/* Target [0x08058C0C, 0x08058C46), 58 complete bytes:
 * 00b581b0b5204000694672f0fbfa031c0021009881420cda021c8800c0188078
 * 002801d0012005e0481c0004010c9142f3db002001b002bc0847
 */
u8 func_08058C0C(void)
{
    InventoryRecord08058C0C *records;
    s32 count;
    u16 i;

    records = func_080CB210(0x16A, &count);
    for (i = 0; i < count; i++) {
        if (records[i].quantity != 0)
            return 1;
    }
    return 0;
}
