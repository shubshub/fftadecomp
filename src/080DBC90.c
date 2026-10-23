#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    s8 field_1f;
} Object080DBC90;

void func_080DBC90(Object080DBC90 *object, s8 value)
{
    object->field_1f = value;
}
