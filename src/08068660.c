#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord08068660;

typedef struct {
    u8 *field_00;
    u8 unknown_04[8];
    u8 field_0C;
    u8 unknown_0D[0xA7];
    u8 field_B4[0];
} Object08068660;

typedef void (*Initialize08068660)(void *destination, u32 size);

extern Initialize08068660 g_callbacks_0836D4B8[];
extern u8 data_08393ACA[];
extern u32 func_08067F14(InventoryRecord08068660 **output, u8 key);

/* Complete [0x08068660, 0x080686C0): 96 bytes.
 * Target: 70b5051c134cb43022680821d9f0eefd0020287328681049401822682021d9f0e5fd00260d48341821780020fff742fc002808d0281cb430297b401821780170287b013028730136052eebdd70bc01bc00470000b8d43608040a0000ca3a3908
 */
void func_08068660(Object08068660 *object)
{
    s32 index;

    g_callbacks_0836D4B8[0](object->field_B4, 8);
    object->field_0C = 0;
    g_callbacks_0836D4B8[0](object->field_00 + 0xA04, 32);
    for (index = 0; index < 6; index++) {
        if (func_08067F14(0, data_08393ACA[index])) {
            object->field_B4[object->field_0C] = data_08393ACA[index];
            object->field_0C++;
        }
    }
}
