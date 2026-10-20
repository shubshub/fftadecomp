#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

void *func_08125578(u32 selector);
u8 func_080C8348(void *object);
u8 func_080CD92C(void *object);
u8 func_080CD95C(void *object);
u8 func_080CD9A4(void *object);
u8 func_080CD9BC(void *object);

u32 func_08123C58(ScriptContext *context, const u8 *script)
{
    void *object = func_08125578(script[1]);

    if (object == 0)
        return 0x110;
    if (!func_080C8348(object) && !func_080CD92C(object) && !func_080CD95C(object) &&
        !func_080CD9A4(object) && !func_080CD9BC(object)) {
        u32 displacement = script[2] | (script[3] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
