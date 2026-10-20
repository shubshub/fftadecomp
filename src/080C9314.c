#include "ffta.h"

typedef struct {
    u8 unknown_00[5];
    u8 first;
    u8 unknown_06;
    u8 second;
    u8 unknown_08[0xF8];
    u8 value;
} RecordObject;

u32 func_080C8570(u8 first, u8 second, u8 selector);

u16 func_080C9314(const void *data)
{
    const RecordObject *object = data;
    u32 value;

    if (object->value != 0)
        value = object->value;
    else
        value = func_080C8570(object->first, object->second, 0);
    return value + 0x247;
}
