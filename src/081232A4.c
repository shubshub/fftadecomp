#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptObject;

void *func_08125578(u32 selector);

u32 func_081232A4(void *context, const u8 *script)
{
    ScriptObject *object = func_08125578(script[1]);

    if (object != 0)
        object->flags |= 0x100;
    return 0x110;
}
