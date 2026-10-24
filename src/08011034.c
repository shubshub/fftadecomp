#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 field_0e;
    u16 field_10;
} Struct08011034;

void func_08011034(Struct08011034 *object, u16 value)
{
    object->field_0e = value;
    object->field_10 = 0;
}
