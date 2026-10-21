#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} FlaggedObject;

void func_081486C8(FlaggedObject *object, u8 enabled, u8 flag40)
{
    if (enabled) {
        object->flags |= 0x20;
        if (flag40) {
            object->flags |= 0x40;
        } else {
            object->flags &= ~0x40;
        }
    } else {
        object->flags &= ~0x20;
        object->flags &= ~0x40;
    }
}
