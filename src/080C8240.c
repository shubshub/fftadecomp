#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptData;

u8 func_080C8240(void *data)
{
    ScriptData *object = data;
    u8 result = 0;

    if (object != 0) {
        u16 flags = object->flags & 0x8000;
        result = flags != 0;
    }
    return result;
}
