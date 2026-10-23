#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} Object0800BDA4;

/* 0x0800BDA4-0x0800BDCC: 40 bytes, including alignment and the trailing literal pool. */
void func_0800BDA4(Object0800BDA4 *object, u8 enabled)
{
    if (enabled)
        object->flags |= 0x0100;
    else
        object->flags &= 0xFEFF;
}
