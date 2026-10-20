#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptObject;

u8 func_080C832C(const ScriptObject *object)
{
    u8 result = 0;

    if (object != 0) {
        u16 flags = object->flags & 0x40;

        result = flags != 0;
    }
    return result;
}
