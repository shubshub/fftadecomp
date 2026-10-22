#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0A];
    u16 value;
} HalfwordObject;

void func_08020FF0(HalfwordObject *object, u16 value)
{
    object->value = value;
}
