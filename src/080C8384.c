#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 category;
} ScriptObject;

u8 func_080C8384(const ScriptObject *object)
{
    u8 category;

    if (object == 0)
        return 0;
    category = object->category;
    return category >= 6 && category <= 18;
}
