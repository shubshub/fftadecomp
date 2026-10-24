#include "ffta.h"

/* 0x0800BED8 - 4 bytes. */
typedef struct {
    u8 unknown_00[0x0E];
    u16 field_0e;
} Struct0800BED8;

void func_0800BED8(Struct0800BED8 *object, u32 value)
{
    object->field_0e = value;
}
