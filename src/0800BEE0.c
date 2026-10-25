#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} Struct0800BEE0;

/* 0x0800BEE0 - 36 bytes, including alignment and literal pool. */
void func_0800BEE0(Struct0800BEE0 *object, u8 enabled)
{
    if (enabled)
        object->flags |= 0x40;
    else
        object->flags &= ~0x40;
}
