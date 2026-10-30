#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 value_06;
    u8 unknown_07[0x35];
    u8 value_3C;
} Object081304E0;

typedef struct {
    u8 unknown_00[4];
    u16 index;
    u8 kind;
    u8 unknown_07;
} Entry081304E0;

typedef struct {
    u8 unknown_00;
    u8 selector : 5;
    u8 unknown_01_high : 3;
    u8 unknown_02[2];
} TableEntry081304E0;

extern const TableEntry081304E0 data_0852736C[];
extern const u8 *func_080CD480(u8 first, u8 second);

/* Complete target [0x081304E0, 0x0813054A), 106 bytes:
 * 00b582793c300178101c9cf7c9ff011c8879052826d188888000064940184078c006c00e04281dd88000034940180068874600006c7352081c0513083005130834051308380513083c05130840051308052008e0082006e00a2004e00c2002e00f2000e0002002bc0847
 */
s32 func_081304E0(void *unit)
{
    const Object081304E0 *object = unit;
    const Entry081304E0 *entry = (const Entry081304E0 *)
        func_080CD480(object->value_06, object->value_3C);

    if (entry->kind == 5) {
        u32 index = entry->index;
        const TableEntry081304E0 *record = &data_0852736C[index];

        switch (record->selector) {
        case 0:
            return 5;
        case 1:
            return 8;
        case 2:
            return 10;
        case 3:
            return 12;
        case 4:
            return 15;
        }
    }
    return 0;
}
