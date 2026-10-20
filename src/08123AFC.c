#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptObject;

void *func_08125578(u32 selector);

u32 func_08123AFC(ScriptContext *context, const u8 *script)
{
    ScriptObject *object = func_08125578(script[1]);

    if (object != 0 && ((object->flags >> script[2]) & 1)) {
        u32 displacement = script[3] | (script[4] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
