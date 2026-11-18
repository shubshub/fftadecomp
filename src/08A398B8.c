#include "ffta.h"

typedef struct {
    u16 flags;
} Object08A398B8;

/* Table slot 0x08394054 dispatches to the installed Thumb code at 0x03006D04. */
void func_08A398B8(void *target, u8 enabled)
{
    Object08A398B8 *object = target;

    if (enabled)
        object->flags |= 4;
    else
        object->flags &= ~4;
}
