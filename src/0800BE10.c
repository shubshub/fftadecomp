#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} Object0800BE10;

/* 0x0800BE10-0x0800BE34: 36 bytes, including the trailing literal pool. */
void func_0800BE10(Object0800BE10 *object, u32 enabled)
{
    if (enabled)
        object->flags |= 0x0400;
    else
        object->flags &= ~0x0400;
}
