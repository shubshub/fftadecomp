#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} ScriptData;

u8 func_080C817C(void *data)
{
    ScriptData *object = data;
    u8 result = 0;

    if (object != 0 && object->index > 1)
        result = 1;
    return result;
}
