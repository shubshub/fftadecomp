#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} Struct0800C64C;

void func_0800C64C(Struct0800C64C *object)
{
    object->flags |= 1;
}
