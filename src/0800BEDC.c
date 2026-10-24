#include "ffta.h"

/* 0x0800BEDC - 4 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 field_10;
} Struct0800BEDC;

void func_0800BEDC(Struct0800BEDC *object, u32 value)
{
    object->field_10 = value;
}
