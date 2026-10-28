#include "ffta.h"

typedef struct Object08029D20 {
    u8 unknown_0000[0x1089];
    u8 value;
} Object08029D20;

/* 08029D20..08029D2C: 12 bytes, 4 instructions, including the offset literal. */
void func_08029D20(Object08029D20 *object, u8 value)
{
    object->value = value;
}
