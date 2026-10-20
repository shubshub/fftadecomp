#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD6];
    u16 value;
} ValueObject;

typedef struct {
    ValueObject *data;
    u8 unknown_04[0x24];
    u8 adjustment_index;
} AdjustmentState;

s32 func_080C7EA4(const void *object, u32 selector);

void func_08131E90(AdjustmentState *object)
{
    s32 value = func_080C7EA4(object->data, 0x26);

    value += ((s16 *)((u8 *)object + 0x20))[object->adjustment_index];
    if (value > 10)
        value = 10;
    object->data->value = value;
}
