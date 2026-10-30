#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CBD34(u16 identifier);

/* 0x080CC7F8..0x080CC86A: 114 complete bytes.
 * Target: f0b54f464646c0b481b081460906090e8846052901d0012001e0b52040006946fef7fafc071c002500260098864218daa800c4192088fff781fa0006000e404509d1a078002806d0b000484421680160701c0004060c681c0004050c00988542e6db301c01b018bc9846a146f0bc02bc0847.
 */
u16 func_080CC7F8(InventoryRecord *output, u8 selector)
{
    InventoryRecord *records;
    s32 count;
    u16 i;
    u16 written;

    if (selector != 5)
        records = func_080CB210(1, &count);
    else
        records = func_080CB210(0x16A, &count);
    for (i = 0, written = 0; i < count; i++) {
        if (func_080CBD34(records[i].identifier) == selector &&
            records[i].quantity != 0) {
            output[written] = records[i];
            written++;
        }
    }
    return written;
}
