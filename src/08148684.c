#include "ffta.h"

struct ObjectState {
    u16 state;
    u16 flags;
};

enum {
    OBJECT_FLAG_10 = 0x10
};

void func_08148684(struct ObjectState *object, u8 mode)
{
    if (mode == 1)
        object->flags &= (u16)~OBJECT_FLAG_10;
    else
        object->flags |= OBJECT_FLAG_10;
}
