/* 0x08011140: 6 bytes, complete body ends at 0x08011146. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2B];
    u8 field_2b;
} Struct08011140;

void func_08011140(Struct08011140 *object, s8 value)
{
    object->field_2b = (u8)value;
}
