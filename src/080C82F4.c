#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptObject;

u8 func_080C82F4(const ScriptObject *object)
{
    u8 result = 0;

    if (object != 0) {
        u16 flags = object->flags & 0x10;

        result = flags != 0;
    }
    return result;
}
