#include "ffta.h"

/* Installed at 0x03006CD0. Table slot 0x08394048 dispatches this callback. */
typedef struct {
    u16 flags;
} Object08A39884;

void func_08A39884(Object08A39884 *object, u8 clear)
{
    if (clear)
        object->flags &= ~8;
    else
        object->flags |= 8;
}
