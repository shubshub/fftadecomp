#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} FlaggedObject;

void func_08148704(FlaggedObject *object, u8 enabled, u8 index)
{
    if (enabled) {
        object->flags |= 0x20;
        object->flags |= 0x80u << index;
    } else {
        object->flags &= ~0x20;
        object->flags &= ~0x780;
    }
}
