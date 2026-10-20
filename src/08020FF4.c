#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 value;
} HalfwordObject;

void func_08020FF4(HalfwordObject *object, u8 value)
{
    object->value = value;
}
