/* 0x080112E8: 6 bytes, complete body ends at 0x080112EE. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x31];
    u8 field_31;
} Struct080112E8;

void func_080112E8(Struct080112E8 *object, u8 value)
{
    object->field_31 = value;
}
