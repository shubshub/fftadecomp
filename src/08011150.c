#include "ffta.h"

typedef struct Struct08011150 {
    u8 unknown_00[0x2C];
    s16 field_2c;
} Struct08011150;

/* 0x08011150-0x08011154: 4 bytes. */
void func_08011150(Struct08011150 *object, s16 value)
{
    object->field_2c = value;
}
