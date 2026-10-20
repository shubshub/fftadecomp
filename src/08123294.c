#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u16 value;
    u8 state;
} ScriptContext;

u32 func_08123294(ScriptContext *context, const u8 *script)
{
    context->state = 7;
    context->value = script[1];
    return 0x11C;
}
