/* 0x08013428 - Set the active object's halfword at offset 0x24. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u16 value_24;
} Object08013428;

extern Object08013428 *data_0200918C;

void func_08013428(u16 value)
{
    data_0200918C->value_24 = value;
}
