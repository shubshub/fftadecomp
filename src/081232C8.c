#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s32 value : 16;
    u32 : 16;
    u32 amount : 16;
} ScriptParameters;

void func_08127C54(void *context, ScriptParameters parameters);

u32 func_081232C8(void *context, const u8 *script)
{
    ScriptParameters parameters;

    parameters.selector = script[1];
    parameters.value = script[2] | (script[3] << 8);
    parameters.mode = script[4];
    parameters.amount = script[5] | (script[6] << 8);
    func_08127C54(context, parameters);
    return 0x115;
}
