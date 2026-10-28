#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
} FlaggedObject;

/* 0x0809993C..0x0809995C: 32 bytes. */
void func_0809993C(FlaggedObject *object, u8 enabled)
{
    if (enabled)
        object->flags |= 0x20;
    else
        object->flags &= ~0x20;
}
